// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimNotify_HitAttackCheck.h"
#include "Character/ABAnimationAttackInterface.h"

void UABAnimNotify_HitAttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super:: Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{

		//UE_LOG(LogTemp, Log, TEXT("%s"), *MeshComp->GetOwner()->GetName());
		IABAnimationAttackInterface*AttackInterface=Cast<IABAnimationAttackInterface>(MeshComp->GetOwner());//엑터타입으로 넘겨주는것 월드를 구성하는 기본단위이기 때문이다. 추가기능이지만 캐스팅 하는것도 가능함
		if (AttackInterface)
		{
			AttackInterface->AttackHitCheck();
		}

	}
}
