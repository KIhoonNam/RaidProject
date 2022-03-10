// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MeleeAttack.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("MeleeAttack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	auto Enemy = Cast<AEnemyCharacterBase>(Controller->GetPawn());

	FString MName = "Melee";

	if (montage_has_finished(Enemy))
	{
		Controller->StopMovement();

		Enemy->PlayMontage(Enemy->GetMontage()[MName]);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_MeleeAttack::montage_has_finished(class AEnemyCharacterBase* const Enemy)
{
	for (auto i : Enemy->GetMontage())
	{
		if (!Enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(i.Value))
			return false;
	}
	return true;
}
