// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RotationEnemy.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBTTask_RotationEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_RotationEnemy();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds) override;

private:

	float CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB);

	float Percivie = 15.0f;

	float PrecisionDot;
};
