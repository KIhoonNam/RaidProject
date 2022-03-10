// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Animation/MyMeleeAttackNotifyState.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/Character/BladeCharacter.h>

void UMyMeleeAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		Player = Cast<ABladeCharacter>(MeshComp->GetOwner());

		if (Player != NULL)
		{
			Player->SetAttackBox(true);
		}
	}
}

void UMyMeleeAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{

		if (Player != NULL)
		{
			Player->SetAttackBox(false);
		}
	}
}
