// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/EnemyControllerBase.h"
#include "IggyEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API AIggyEnemyController : public AEnemyControllerBase
{
	GENERATED_BODY()
public:
	AIggyEnemyController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;


	virtual void Tick(float DeltaSecond) override;

	virtual FRotator GetControlRotation() const override;

	virtual void OnSenseUpdated(AActor* actor, FAIStimulus const Stimulus) override;
};
