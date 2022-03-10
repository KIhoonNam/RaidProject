// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CharacterSpeedChange.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UBTService_CharacterSpeedChange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_CharacterSpeedChange();

	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float speed = 600.0f;
};
