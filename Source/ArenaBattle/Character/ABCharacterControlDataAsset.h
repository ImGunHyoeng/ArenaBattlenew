// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABCharacterControlDataAsset.generated.h"


/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterControlDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControlRotationYaw : 1;//b�� �Ҹ��� Ÿ������ ����ϰ� �; ��� ,bool�� ����ϸ� ������ ũ�Ⱑ Ȯ���̾ȵ�

	UPROPERTY(EditAnywhere, Category = Pawn)
		uint32 bUseControlRotationPitch : 1;

	UPROPERTY(EditAnywhere, Category = Pawn)
		uint32 bUseControlRotationRoll : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
		FRotator RotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
		uint32 bUseControlDesiredRotation : 1;//���������ӿ� ���ļ� ������ ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
		uint32 bOrientRotationToMovement : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		TObjectPtr<class UInputMappingContext> InputMappingContext;

	//Spring arm Section ����� ���� ���ϱ� ����
	UPROPERTY(EditAnywhere, Category = SpringArm)
		float TargetArmLength;

	UPROPERTY(EditAnywhere, Category = SpringArm)
		FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, Category = SpringArm)
		uint32 bUsePawnControlRotation : 1;//������ ũ��� ���� �ڷ����̱⿡ �̰��� ����ϴ°�

	UPROPERTY(EditAnywhere, Category = SpringArm)
		uint32 bDoCollisionTest : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
		uint32 bInheritYaw : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
		uint32 bInheritRoll : 1;
	
	UPROPERTY(EditAnywhere, Category = SpringArm)
		uint32 bInheritPitch : 1;

};
