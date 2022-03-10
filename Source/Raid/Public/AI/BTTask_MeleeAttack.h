// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_MeleeAttack();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
private:
	bool montage_has_finished(class AEnemyCharacterBase* const Enemy);
};
