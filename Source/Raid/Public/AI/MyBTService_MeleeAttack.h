// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API UMyBTService_MeleeAttack : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UMyBTService_MeleeAttack();

	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float Meleerange = 25.0f;

	bool montage_has_finished(class AEnemyCharacterBase* const Enemy);
	
};
