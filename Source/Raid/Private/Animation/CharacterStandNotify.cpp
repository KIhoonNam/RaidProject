// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterStandNotify.h"
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/Character/BladeCharacter.h>


void UCharacterStandNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		class AMyCharacter* Player = Cast<ABladeCharacter>(MeshComp->GetOwner());

		if (Player != NULL)
		{
			Player->SetState(ECharacterState::IDLE);
			Player->SetInfinity(false);
		}
	}
	
}