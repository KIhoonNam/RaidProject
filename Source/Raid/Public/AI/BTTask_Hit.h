// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Hit.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTTask_Hit : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Hit();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
