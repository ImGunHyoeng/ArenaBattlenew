// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameModeBase.h"
#include "Character/ABCharacterNonPlayer.h"


void AABGameModeBase::Spawn()
{
	SpawnDelegate.ExecuteIfBound();
	if (CurCount < MaxCountEnemy)
	{
		CurCount++;
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
	}
}
void AABGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	double pos_x = (rand() % 100) * 7;
	double pos_y = (rand() % 100) * 7;
	if ((int)pos_x % 2 == 1)pos_x *= -1;
	if ((int)pos_y % 2 == 1)pos_y *= -1;
	FVector position(pos_x, pos_y, 90);
	//MaxCountEnemy = 5;
	FRotator rotation = FRotator::ZeroRotator;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AABCharacterNonPlayer>(TargetClass, position, rotation);
	while (SpawnedActor == NULL)
	{
		pos_x = (rand() % 100) * 7;
		pos_y = (rand() % 100) * 7;
		position.Set(pos_x, pos_y, 90);
		SpawnedActor = GetWorld()->SpawnActor<AABCharacterNonPlayer>(TargetClass, position, rotation);
	}
	
	CharacterBase->ResetCurcount();
	//CurCount++;
	//UE_LOG(LogTemp, Log, TEXT("spawn %d"),CurCount);
}
AABGameModeBase::AABGameModeBase()
{
	// Default Pawn Class
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (ThirdPersonClassRef.Class)
	//{
	//	DefaultPawnClass = ThirdPersonClassRef.Class;
	//}

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Character/BP_CharacterPlayer.BP_CharacterPlayer_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// Player Controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CoreUObject.Class'/Script/ArenaBattle.ABPlayerController'"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AABCharacterNonPlayer> TargetRef(TEXT("/Script/CoreUObject.Class'/Script/ArenaBattle.ABCharacterNonPlayer'"));
	if (TargetRef.Class)
	{
		TargetClass = TargetRef.Class;
	}
	//Gamemode = this;
	//MaxCountEnemy = 5;
}

