// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameModeBase.h"
#include "Character/ABCharacterNonPlayer.h"

void AABGameModeBase::Spawn()
{
	
}
void AABGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	FVector position = FVector::ZeroVector;
	GetWorld()->SpawnActor<AABCharacterNonPlayer>(AABCharacterNonPlayer::StaticClass(), position);
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
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<AABCharacterNonPlayer> SecondPawnRef(TEXT("/Script/CoreUObject.Class'/Script/ArenaBattle.ABCharacterNonPlayer'"));
	if (SecondPawnRef.Object)
	{
		SecondPawnClass = SecondPawnRef.Object;
	}

}
