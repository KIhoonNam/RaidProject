// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TargetPlayerLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBTTask_TargetPlayerLocation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_TargetPlayerLocation();
	

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		bool search_random = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float search_radius = 150.0f;

	FTimer deltatime;
};
