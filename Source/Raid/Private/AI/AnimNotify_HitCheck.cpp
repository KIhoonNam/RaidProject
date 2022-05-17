// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AnimNotify_HitCheck.h"
#include <Raid/Public/Character/EnemyCharacterBase.h>
#include <Raid/Public/Controller/EnemyControllerBase.h>

void UAnimNotify_HitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		Player = Cast<AEnemyCharacterBase>(MeshComp->GetOwner());
		if (Player != NULL)
			EnemyController = Cast<AEnemyControllerBase>(Player->GetController());
		if (EnemyController != NULL)
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(bb_Keys::hit_check, false);
		}

	}
}