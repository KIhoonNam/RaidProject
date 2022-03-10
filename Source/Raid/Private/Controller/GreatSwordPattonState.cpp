// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Controller/GreatSwordPattonState.h>
#include <Raid/Public/Character/GreatSwordCharacter.h>

void UGreatSwordPattonState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{


		Character = Cast<AGreatSwordCharacter>(MeshComp->GetOwner());


		if (Character != NULL)
		{
		}
	}
}

void UGreatSwordPattonState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UGreatSwordPattonState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		if (Character != NULL)
		{
			Character->Attack = false; 
		}
	}

}
