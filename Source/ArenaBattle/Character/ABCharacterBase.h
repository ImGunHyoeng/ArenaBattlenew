// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere,Category=CharacterControl,Meta=(AllowPrivateAccess="true"))//Meta: �����̺��� ���� ������ �־ �����Ϳ��� ���ٵǵ��� �ϴ°�
	TMap<ECharacterControlType, class UABCharacterControlDataAsset*> CharacterControlManager;

	virtual void SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData);//�տ��� ������ ������ �߱⿡ �ߺ� ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> ComboActionMontage;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackData,Meta=(AllowPriviteAccess="true"))
		TObjectPtr<class UABComboActionData> ComboActionData;

	
	void ProcessComboAttack();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage,bool IsEnded);//�ִϸ��̼��� ������ Ÿ�ֿ̹� ȣ��ǵ��� ��������Ʈ�� ���ؼ� �������Ѿ��Ѵ�.

	int32 CurrentCombo = 0;

	FTimerHandle ComboTimerHandle;//Ÿ�̸� ���� �ִϸ��̼� �ð� üũ��
	bool HasNextComboCommand = false;//UPROPERTY�� ����Ұ� �ƴϱ⿡ ���� üũ ���ʿ� x

	void SetComboCheckTimer();
	void ComboCheck();
};
