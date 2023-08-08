// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameModeBase.generated.h"

/**
 * 
 */
//DECLARE_DYNAMIC_DELEGATE(FSpawnDelegate);

UCLASS()
class ARENABATTLE_API AABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TSubclassOf<class AABCharacterNonPlayer> TargetClass;

	virtual void BeginPlay() override;
	AABGameModeBase();
	class AABCharacterBase* CharacterBase;

	//FSpawnDelegate SpawnDelegate;
	//UFUNCTION()
	//	void Spawn();
	
	/*int32 MaxCountEnemy;
	int32 CurCount;*/
};
