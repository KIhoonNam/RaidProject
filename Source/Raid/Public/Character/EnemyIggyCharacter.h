// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyCharacterBase.h"
#include "EnemyIggyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API AEnemyIggyCharacter : public AEnemyCharacterBase
{
	GENERATED_BODY()
public:
	AEnemyIggyCharacter();

public:
	virtual void PlayMontage(UAnimMontage* _montage) override;

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform)override;

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;	
};
