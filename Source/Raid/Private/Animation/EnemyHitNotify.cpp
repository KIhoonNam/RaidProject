// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyHitNotify.h"
#include <Raid/Public/Character/EnemyCharacterBase.h>
#include <Raid/Public/Controller/EnemyControllerBase.h>

void UEnemyHitNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		Player = Cast<AEnemyCharacterBase>(MeshComp->GetOwner());
		if(Player != NULL)
		EnemyController = Cast<AEnemyControllerBase>(Player->GetController());

	}
}

void UEnemyHitNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{

		if (EnemyController != NULL)
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(bb_Keys::hit_check, false);
		}
	}
}
