// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT_MovePlayer.h"

#include "NavigationSystem.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UBT_MovePlayer::UBT_MovePlayer()
{
	NodeName = TEXT("Move Player");
}

EBTNodeResult::Type UBT_MovePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controll = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	FVector const Location = Controll->GetBlackBoard()->GetValueAsVector(bb_Keys::target_location);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controll, Location);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
