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
	UPROPERTY(EditAnywhere,Category=CharacterControl,Meta=(AllowPrivateAccess="true"))//Meta: 프라이빗의 값을 가지고 있어도 에디터에서 접근되도록 하는것
	TMap<ECharacterControlType, class UABCharacterControlDataAsset*> CharacterControlManager;

	virtual void SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData);//앞에서 전방위 선언을 했기에 중복 사용안한

};
