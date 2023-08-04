// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/ABAnimationAttackInterface.h"
#include "ABCharacterBase.generated.h"


UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter,public IABAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere,Category=CharacterControl,Meta=(AllowPrivateAccess="true"))//Meta: 프라이빗의 값을 가지고 있어도 에디터에서 접근되도록 하는것
	TMap<ECharacterControlType, class UABCharacterControlDataAsset*> CharacterControlManager;

	virtual void SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData);//앞에서 전방위 선언을 했기에 중복 사용안한

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> ComboActionMontage;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> DeadMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackData,Meta=(AllowPriviteAccess="true"))
		TObjectPtr<class UABComboActionData> ComboActionData;



	
	void ProcessComboAttack();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage,bool IsEnded);//애니메이션이 끝나는 타이밍에 호출되도록 델리게이트를 통해서 연동시켜야한다.

	int32 CurrentCombo = 0;

	FTimerHandle ComboTimerHandle;//타이머 세팅 애니메이션 시간 체크용
	bool HasNextComboCommand = false;//UPROPERTY로 사용할것 아니기에 공간 체크 할필요 x

	void SetComboCheckTimer();
	void ComboCheck();

	void SetDead();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	
	virtual void AttackHitCheck()override;
};
