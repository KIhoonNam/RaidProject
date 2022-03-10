// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacter.h"
#include "BladeCharacter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RAID_API ABladeCharacter : public AMyCharacter
{
	GENERATED_BODY()
public:
		ABladeCharacter(const FObjectInitializer& ObjectInitializer);

		virtual ~ABladeCharacter();

	UFUNCTION()
		virtual void SetSkill() override;

	UFUNCTION()
		virtual float GetDashCool() override;

	UFUNCTION(BlueprintCallable)
		virtual void DashAnimMontagePlay() override;
protected:
	
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	virtual void BeginPlay() override;



};
