// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABCharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UABCharacterDataAsset();

	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControlRotationYaw : 1;//b는 불리언 타입으로 사용하고 싶어서 등록 ,bool을 사용하면 데이터 크기가 확정이안됨
	
	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControlRotationPitch : 1;
	
	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControlRotationRoll : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = CharacterMovement)
	FRotator RotationRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
	uint32 bUseControlDesiredRotation : 1;//여러프레임에 거쳐서 프레임 변경
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
	uint32 bOrientRotationMovement : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	//Spring arm Section 어깨와 팔을 비교하기 위함
	UPROPERTY(EditAnywhere, Category = SpringArm)
	float TargetArmLength;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	FRotator RelativeRotation;
	
	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bUsePanControlRotation : 1;//버스의 크기와 같은 자료형이기에 이것을 사용하는것
	
	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bDoCollisionTest: 1;
};
