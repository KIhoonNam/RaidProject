// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ActionCheck.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBTService_ActionCheck : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ActionCheck();

	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	

private:

	bool montage_has_finished(class AEnemyCharacterBase* const Enemy);
	
};
