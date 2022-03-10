// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterStNotifyState.h"
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/Character/BladeCharacter.h>


void UCharacterStNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		time = 0;
		Player = Cast<ABladeCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->SetState(ECharacterState::ABNORMAL);
			if (GEngine)
			{

				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(TotalDuration));
			}
		}
	}
	

}

void UCharacterStNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	time += FrameDeltaTime;

	if (time >= 2.36)
		if(Player != NULL)
		Player->SetInfinity(true);

}

void UCharacterStNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{

		if (Player != NULL)
		{
			if(time >= 3.20)
				Player->SetState(ECharacterState::IDLE);
			Player->SetInfinity(false);
			if (GEngine)
			{


				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(time));

				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("End"));
			}
		}
	}
}


