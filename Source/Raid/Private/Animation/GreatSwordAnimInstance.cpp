// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Animation/GreatSwordAnimInstance.h>
#include <Raid/Public/Character/GreatSwordCharacter.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
UGreatSwordAnimInstance::UGreatSwordAnimInstance()
{

}

void UGreatSwordAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AGreatSwordCharacter>(TryGetPawnOwner());
}

void UGreatSwordAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character != NULL)
		CharacterSpeed = Character->GetVelocity().Size();
}
