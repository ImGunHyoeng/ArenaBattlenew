// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
UABAnimInstance::UABAnimInstance()
{
}

void UABAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());//캐릭터이기에 형변환해줌
	if (Owner)
	{
		Movement=Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	Velocity = Movement->Velocity;
	GroundSpeed = Velocity.Size2D();//2차원으로 값을 계산해줌
}
