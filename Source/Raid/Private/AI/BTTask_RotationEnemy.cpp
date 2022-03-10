// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RotationEnemy.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>


UBTTask_RotationEnemy::UBTTask_RotationEnemy()
{
	NodeName = TEXT("Rotation");
}

EBTNodeResult::Type UBTTask_RotationEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Controller = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(Controller->GetCharacter());

	EBTNodeResult::Type Result = EBTNodeResult::Succeeded;
	PrecisionDot = FMath::Cos(FMath::DegreesToRadians(Percivie));
	auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector const player_location = Player->GetActorLocation();
	auto Distance = UKismetMathLibrary::FindLookAtRotation(Enemy->GetActorLocation(), player_location);
	auto Direct = FMath::RInterpTo(Enemy->GetActorRotation(), Distance, 0.2f, 1.0f);

	const float AngleDifference = CalculateAngleDifferenceDot(Enemy->GetActorForwardVector()
		, (player_location - Enemy->GetActorLocation()));

	if (Enemy != nullptr&& Enemy->GetEnemyType() == EEnemyType::IDLE)
	{
		if (AngleDifference >= PrecisionDot)
		{
			Enemy->SetEnemyType(EEnemyType::ATTACK);

			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
			
		}
		else
		{
			
				Enemy->SetActorRotation(Direct);
			
		}
		
	}
	else if(Enemy->GetEnemyType() == EEnemyType::ATTACK)
	{
		return EBTNodeResult::Failed;
	}



	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Result;
}

void UBTTask_RotationEnemy::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

}

float UBTTask_RotationEnemy::CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB)
{
	return (VectorA.IsNearlyZero() || VectorB.IsNearlyZero())
		? 1.f
		: VectorA.CosineAngle2D(VectorB);;
}
