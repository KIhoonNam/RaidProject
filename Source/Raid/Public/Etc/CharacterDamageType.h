// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "CharacterDamageType.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UCharacterDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool Rigid = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Falldown = false;
	
};
