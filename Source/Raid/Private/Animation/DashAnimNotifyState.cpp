// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Animation/DashAnimNotifyState.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Raid/Public/Controller/MyPlayerController.h>
#include <Raid/Public/Character/BladeCharacter.h>

#include <Engine.h>

void UDashAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{


		Player = Cast<ABladeCharacter>(MeshComp->GetOwner());

		
		time = 0;
		if (Player != NULL)
		{

				Controll = Cast<AMyPlayerController>(Player->GetController());
				Controll->SetAction(true);
				if (Player->GetState() == ECharacterState::ATTACK)
				{
					Player->ForwardMove(2500, 5000);
				}
		}
	}
}
void UDashAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{


		time += FrameDeltaTime;
		
		if (Player != NULL)
		{
		if (time <= 0.37f)
		{
			
		
			
		}
		else
		{
			Player->GetMovementComponent()->StopMovementImmediately();
		}
		}
	}
}

void UDashAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		if (Player != NULL)
		{
			
			if (Controll != NULL)
			{
				if (Player->GetState() == ECharacterState::ATTACK)
				{
					Controll->SetClickDash(false);
					Player->SetState(ECharacterState::IDLE);
					Player->SetInfinity(false);
					Player->SetStop(false);
				}
				else if (Player->GetState() == ECharacterState::ABNORMAL)
				{
					Controll->SetClickDash(false);
					Player->SetState(ECharacterState::IDLE);
					Player->SetInfinity(false);
					Player->SetStop(false);
				}
			}
		}
	}

}
