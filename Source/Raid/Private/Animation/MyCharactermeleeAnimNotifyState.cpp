// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Animation/MyCharactermeleeAnimNotifyState.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Raid/Public/Controller/MyPlayerController.h>
#include <Raid/Public/Character/BladeCharacter.h>

#include <Engine.h>

void UMyCharactermeleeAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() !=NULL)
	{
	
		
		Player = Cast<ABladeCharacter>(MeshComp->GetOwner());
		
		
		if(Player != NULL)
		{
			Controll = Cast<AMyPlayerController>(Player->GetController());
			call = false;
			Controll->SetAction(true);
			if (GEngine)
			{
				
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Begin"));
			}
		}
	}
	
}

void UMyCharactermeleeAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{


	
		if(Controll != NULL)
			Controll->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Player != NULL)
		{
			if (!call && Controll->GetClickAttack())
			{
				if (Player->GetAttackIndex() != 0)
				{
					Player->SetAttackIndex(1);
					call = true;
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::FromInt(Player->GetAttackIndex()));
					}
				}
				else
				{
					
				}
			}
			
		}
	}
}

void UMyCharactermeleeAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{



		if (Player != NULL)
		{
			if (call)
			{
				if (Controll != NULL)
				Controll->SetMeleeRotation(Player,Hit);
				Player->AnimMontagePlay();
				if (Player->GetAttackIndex() == 4)
					Player->SetAttackIndex(-4);
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("True"));
				}
				
			}
			else
			{
				Player->SetAttackIndex(-(Player->GetAttackIndex() - 1));
				Player->AttackAble(false);
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("False"));
				Player->SetState(ECharacterState::IDLE);
			}
		
		}
	}
}
