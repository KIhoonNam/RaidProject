// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TargetPlayerLocation.h"

#include "NavigationSystem.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UBTTask_TargetPlayerLocation::UBTTask_TargetPlayerLocation()
{
	NodeName = TEXT("TargetPlayerLocation");
}

EBTNodeResult::Type UBTTask_TargetPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get player Character and the NPC-s Controller
	auto const Controller = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	auto Enemy = Cast<AEnemyCharacterBase>(Controller->GetPawn());


	
	auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector const player_location = Player->GetActorLocation();
	auto Distance = UKismetMathLibrary::FindLookAtRotation(Enemy->GetActorLocation(), Player->GetActorLocation());

	auto Direct = FMath::RInterpTo(Enemy->GetActorRotation(), Distance, 0.05f, 1.0f);
	if (search_random)
	{

		FNavLocation loc;

		UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nullptr == NavSystem) {
			//navi mesh가 없다면 실패를 반환
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
			return EBTNodeResult::Failed;
		}

		if (NavSystem->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
		{
			if (Enemy->GetEnemyType() == EEnemyType::IDLE)
			{
				Enemy->SetEnemyType(EEnemyType::MOVE);
				Controller->GetBlackBoard()->SetValueAsVector(AEnemyControllerBase::TargetLocation, loc.Location);
				Controller->GetBlackBoard()->SetValueAsObject(bb_Keys::player_object, Player);
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Controller->GetBlackBoard()->GetValueAsObject(bb_Keys::player_object)->GetName());

			//Enemy->SetActorRotation(Direct);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextPosSuccess!"));
		}
	}
	else
	{

		Controller->GetBlackBoard()->SetValueAsVector(AEnemyControllerBase::TargetLocation, player_location);

	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
