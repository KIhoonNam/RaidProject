// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MovePlayer.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UBTTask_MovePlayer::UBTTask_MovePlayer()
{
	NodeName = TEXT("Move Player");
}

EBTNodeResult::Type UBTTask_MovePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controll = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	auto Enemy = Cast<AEnemyCharacterBase>(Controll->GetPawn());
	FVector const Location = Controll->GetBlackBoard()->GetValueAsVector(bb_Keys::target_location);

	if (!Controll->GetBlackBoard()->GetValueAsBool(bb_Keys::player_is_in_melee_range))
		if (Enemy->GetEnemyType() == EEnemyType::MOVE)
		{
			Controll->MoveToLocation(Location);
		}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}