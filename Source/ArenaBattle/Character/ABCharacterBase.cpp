// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/ABCharacterDataAsset.h"
#include "ABCharacterControlDataAsset.h"
#include "Character/ABComboActionData.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"
#include "Character/ABCharacterNonPlayer.h"
#include "Game/ABGameModeBase.h"

int32 AABCharacterBase::MaxSpawncount = 5;
int32 AABCharacterBase::Curcount = 1;
// Sets default values
AABCharacterBase::AABCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCapsule"));

	// SkeletalMesh Component
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	// CharacterMovement Component
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Tusk.SK_CharM_Tusk'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Animation/ABC_CharacterAnim.ABC_CharacterAnim_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UABCharacterControlDataAsset> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlDataAsset'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}//캐릭터 컨트롤 에셋을 가져와준다.
	
	static ConstructorHelpers::FObjectFinder<UABCharacterControlDataAsset> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlDataAsset'/Game/ArenaBattle/CharacterControl/ABC_Queter.ABC_Queter'"));
	if (QuaterDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}


	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/ Script/Engine.AnimMontage'/Game/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}
	
	static ConstructorHelpers::FClassFinder<AABCharacterNonPlayer> TargetRef(TEXT("/Script/CoreUObject.Class'/Script/ArenaBattle.ABCharacterNonPlayer'"));
	if (TargetRef.Class)
	{
		TargetClass = TargetRef.Class;
	}
	//ABGameModeBase->SpawnDelegate.BindUFunction(this, FName("Spawn"));
	//(this, &AABCharacterBase::Spawn)
	static ConstructorHelpers::FClassFinder<AABGameModeBase> GameModeRef(TEXT("/Script/CoreUObject.Class'/Script/ArenaBattle.ABGameModeBase'"));
	if (GameModeRef.Class)
	{
		GamemodeData = GameModeRef.Class;
	}
	
	//ABGameModeBase=(new AABGameModeBase());
	//ABGameModeBase();
	//if(ABGameModeBase)
		
}

void AABCharacterBase::ProcessComboAttack()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
	

}

void AABCharacterBase::ComboActionBegin()//콤보 시작시에 실행
{
	CurrentCombo = 1;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);//공격중에는 못움직이도록 설정함

	const float AttackSpeedRate = 1.0f;
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage,AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);//델리게이트 바인드를 시켜줌 섹션이 끝날때 호출 
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsEnded)//델리게이트를 쓴 이유는 애니메이션이 종료되는 시간을 알지 못하기에 델리게이트로 애니메이션에 등록해놓은것.
{
	CurrentCombo = 0;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);//공격중에는 못움직이도록 설정함
}

void AABCharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;//인덱스를 뺀 이유
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));//예외처리 인덱스의 범위가 정상인지 확인해주기 위함

	const float AttackSpeedRate = 1.0f;

	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacterBase::ComboCheck, ComboEffectiveTime, false);//델리게이트로 시간에 따라서 작동될 함수를 체크하며 시간을 가져와줄 핸들도 세팅해줌
	}
}

void AABCharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();//타이머 핸들을 초기화 시켜줌


	if (HasNextComboCommand)
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);

		FName NextSectionName = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionPrefix, CurrentCombo);//점프시키는것

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_JumpToSection(NextSectionName, ComboActionMontage);//원하는 부분으로 이동하는 함수이다

		SetComboCheckTimer();//콤보의 타이머로 사이에 값이 들어오는지 체크
		HasNextComboCommand = false;
	}
}

void AABCharacterBase::SetDead()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//죽었을때 충돌처리가 안되도록 처리함
}

float AABCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	//TODO
	float DelayTimeDestroy = 5.0f;
	float DelayTimeSpawn = 3.0f;

	//FTimerDelegate TimerDelegateDestroy;
	//TimerDelegateDestroy.BindUFunction(this, FName("Destroy"));
	FTimerDelegate TimerDelegateSpawn;
	TimerDelegateSpawn.BindUFunction(this, FName("Spawn"));

	FTimerHandle TimerHandle;


	SetDead();
	/*GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegateDestroy, DelayTimeDestroy, false);*/
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegateSpawn, DelayTimeSpawn, false);
	
	return 0.0f;
}

void AABCharacterBase::Destroy()
{
	AActor::Destroy();
}

void AABCharacterBase::Spawn()
{
	
	AActor::Destroy();
	
	/*ABGameModeBase->SpawnDelegate.Execute();
	ABGameModeBase->SpawnDelegate.*/
	//Cast<AABGameModeBase>(GamemodeData->StaticClass())->Spawn();
	
	/*TSharedRef<AABGameModeBase> LogWriter= Cast<AABGameModeBase>(AABGameModeBase().StaticClass());
	GamemodeData
	SpawnDelegate.BindSP(LogWriter, &AABGameModeBase::Spawn);
	SpawnDelegate.Excute();
	*/
	if (Curcount < MaxSpawncount)
	{
	double pos_x = (rand() % 100) * 7;
	double pos_y = (rand() % 100) * 7;
	if ((int)pos_x % 2 == 1)pos_x *= -1;
	if ((int)pos_y % 2 == 1)pos_y *= -1;
	FVector position(pos_x, pos_y, 90);
	static FRotator rotation = FRotator::ZeroRotator;
	
		AActor* SpawnedActor = GetWorld()->SpawnActor<AABCharacterNonPlayer>(TargetClass, position, rotation);
		while (SpawnedActor == NULL)
		{
			pos_x = (rand() % 100) * 7;
			pos_y = (rand() % 100) * 7;
			position.Set(pos_x, pos_y, 90);
			SpawnedActor = GetWorld()->SpawnActor<AABCharacterNonPlayer>(TargetClass, position, rotation);
		}
		Curcount++;

	}
	
	
	
}

void AABCharacterBase::ResetCurcount()
{
	Curcount = 1;
}

void AABCharacterBase::AttackHitCheck()
{
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack),false,this);

	FHitResult OutHitResult;
	const float AttackRange = 300.0f;
	const float Radius = 50.0f;

	

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;
	//박스의 크기만큼 사이즈

	/*bool bIsHit=GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), ECC_GameTraceChannel3, FCollisionShape::MakeSphere(Radius), Params);*/
	bool bIsHit = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeSphere(Radius), Params);
	if (bIsHit)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(100.0f, DamageEvent, GetController(), this);
		if (Curcount < MaxSpawncount)
		{
			UE_LOG(LogTemp, Log, TEXT("Spawn %d"),Curcount);
			
		}
		else if (Curcount == MaxSpawncount)
		{
			UE_LOG(LogTemp, Display, TEXT("Clear"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("Clear ")));
		}
		
		//Cast<AABCharacterBase>(OutHitResult.GetActor())->SetDead();//상대방에대한 정보를 가져온다.
		//SetDead();
	}
#if ENABLE_DRAW_DEBUG
	//눈으로 보이도록 그리기 #if로 define 되어있는지 안돼어있는지에 대해서 알고 확인하는 것
	FVector CapsulePosition = Start + (End - Start) / 2.0f;
	float HalfHeight = AttackRange / 2.0f;
	FColor Color = bIsHit? FColor::Green :FColor::Red;

	//DrawDebugCapsule(GetWorld(), CapsulePosition, HalfHeight, Radius, FQuat::Identity, Color,false,3.0f);
	DrawDebugCapsule(GetWorld(), CapsulePosition, HalfHeight, Radius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), Color,false,3.0f);

#endif
}

// Called to bind functionality to input
void AABCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AABCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//ABGameModeBase->SpawnDelegate.BindUFunction(this, FName("Spawn"));
	//ABGameModeBase();
	//ABGameModeBase = Cast<AABGameModeBase>(GamemodeData.Get());
	
	//ABGameModeBase->SpawnDelegate.(FName("Spawn"));
		//SpawnDelegate.BindUObject(this, &AABCharacterBase::Spawn)
}

void AABCharacterBase::SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData)
{
	bUseControllerRotationYaw=CharacterControlData->bUseControlRotationYaw;
	
	bUseControllerRotationPitch=CharacterControlData->bUseControlRotationPitch;
	
	bUseControllerRotationRoll=CharacterControlData->bUseControlRotationRoll;

	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
	
	GetCharacterMovement()->bUseControllerDesiredRotation= CharacterControlData->bUseControlDesiredRotation;
	
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
}

