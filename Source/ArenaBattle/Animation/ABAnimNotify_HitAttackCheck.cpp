// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimNotify_HitAttackCheck.h"
#include "Character/ABAnimationAttackInterface.h"

void UABAnimNotify_HitAttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super:: Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{

		//UE_LOG(LogTemp, Log, TEXT("%s"), *MeshComp->GetOwner()->GetName());
		IABAnimationAttackInterface*AttackInterface=Cast<IABAnimationAttackInterface>(MeshComp->GetOwner());//����Ÿ������ �Ѱ��ִ°� ���带 �����ϴ� �⺻�����̱� �����̴�. �߰���������� ĳ���� �ϴ°͵� ������
		if (AttackInterface)
		{
			AttackInterface->AttackHitCheck();
		}

	}
}
