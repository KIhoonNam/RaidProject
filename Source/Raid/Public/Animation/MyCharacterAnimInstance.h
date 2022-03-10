// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacterAnimInstance.generated.h"

class AMyCharacter;
/**
 * 
 */
UCLASS(Blueprintable,hideCategories=AnimInstance,BlueprintType)
class RAID_API UMyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMyCharacterAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float CharacterSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Direction;
	
	

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	AMyCharacter* Character;
};
