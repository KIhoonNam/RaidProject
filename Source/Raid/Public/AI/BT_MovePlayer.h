// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_MovePlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBT_MovePlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBT_MovePlayer();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
