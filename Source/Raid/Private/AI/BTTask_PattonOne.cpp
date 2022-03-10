// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_PattonOne.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UBTTask_PattonOne::UBTTask_PattonOne()
{
	NodeName = TEXT("PattonOne");
}

EBTNodeResult::Type UBTTask_PattonOne::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	auto Enemy = Cast<AEnemyCharacterBase>(Controller->GetPawn());

	FString MName = "PattonOne";

	if (montage_has_finished(Enemy))
	{
		Controller->StopMovement();

		Enemy->PlayMontage(Enemy->GetMontage()[MName]);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_PattonOne::montage_has_finished(AEnemyCharacterBase* const Enemy)
{
	for (auto i : Enemy->GetMontage())
	{
		if (!Enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(i.Value))
			return false;
	}
	return true;
}
