// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Animation/MyCharacterAnimInstance.h>
#include <Raid/Public/Character/MyCharacter.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

UMyCharacterAnimInstance::UMyCharacterAnimInstance()
{

}

void UMyCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	Character = Cast<AMyCharacter>(TryGetPawnOwner());
}

void UMyCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(Character != NULL)
		CharacterSpeed = Character->GetVelocity().Size();
}
