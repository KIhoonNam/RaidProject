// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CharacterSpeedChange.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>


UBTService_CharacterSpeedChange::UBTService_CharacterSpeedChange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("ChangeSpeed");
}

void UBTService_CharacterSpeedChange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	auto const controll = owner_comp.GetAIOwner();

	auto const Enemy = Cast<AEnemyCharacterBase>(controll->GetPawn());

	Enemy->GetCharacterMovement()->MaxWalkSpeed = speed;
}
