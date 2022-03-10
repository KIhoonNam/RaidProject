// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TargetMoveTo.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBTTask_TargetMoveTo : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TargetMoveTo();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float search_radius = 1500.f;

	FTimer deltatime;
};
