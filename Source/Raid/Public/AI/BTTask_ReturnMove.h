// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ReturnMove.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBTTask_ReturnMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ReturnMove();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float search_radius = 1500.f;
};
