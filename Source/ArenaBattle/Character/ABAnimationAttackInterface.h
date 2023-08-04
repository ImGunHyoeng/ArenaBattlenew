// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABAnimationAttackInterface.generated.h"

// This class does not need to be modified.
//그냥 형식
UINTERFACE(MinimalAPI)
class UABAnimationAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
//기능추가
class ARENABATTLE_API IABAnimationAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AttackHitCheck() = 0;
};
