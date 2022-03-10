// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ReturnMove.h"
#include "NavigationSystem.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UBTTask_ReturnMove::UBTTask_ReturnMove()
{
	NodeName = TEXT("ReturnTarget");
}

EBTNodeResult::Type UBTTask_ReturnMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	auto Enemy = Controller->GetPawn();


	if (Enemy == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy Initialize faild!"));
		return EBTNodeResult::Failed;
	}



	FVector Location = Controller->GetBlackBoard()->GetValueAsVector(AEnemyControllerBase::HomePosKey);

	//NextPatrol변수에 임의의 location 데이터를 넣고 다시 TargetLocation키의 value에 값을 넣어준다.


	if(Controller->GetBlackBoard()->GetValueAsBool(bb_Keys::enemy_range_over))
		Controller->GetBlackBoard()->SetValueAsVector(AEnemyControllerBase::TargetLocation, Location);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextPosSuccess!"));
	

	

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
