// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Animation/DashAttackNotifyState.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/Character/BladeCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Raid/Public/Controller/MyPlayerController.h>

#include <Engine.h>
void UDashAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{


		Player = Cast<ABladeCharacter>(MeshComp->GetOwner());
		time = 0;
	
		if (Player != NULL)
		{
			OneTime = false;
			Controll = Cast<AMyPlayerController>(Player->GetController());
			Controll->SetAction(true);
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Go"));
		
		}
	}
}
void UDashAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{


		time += FrameDeltaTime;

		if (Player != NULL)
		{

			if ( time >= 0.2f && !OneTime)
			{

				Player->ForwardMove(1000, 3000);
				OneTime = true;

			}
			else if(time > 0.6f)
				Player->GetCharacterMovement()->StopMovementImmediately();
		}
	}
}


void UDashAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{


		


		if (Player != NULL)
		{
			if (Controll->GetDashAttack() && !Controll->GetDashOne() &&Player->GetState() != ECharacterState::ABNORMAL)
			{
				Controll->QSkill();
				Controll->SetClickDash(true);
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("On"));
			}
			else
			{

				Player->SetState(ECharacterState::IDLE);
				Player->SetStop(false);
				Controll->SetClickDash(false);
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Off"));
				
			}
		}
	}
}
