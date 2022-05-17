// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Hit.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UBTTask_Hit::UBTTask_Hit()
{
	NodeName = TEXT("Hit");
}

EBTNodeResult::Type UBTTask_Hit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AEnemyControllerBase>(OwnerComp.GetAIOwner());
	auto Enemy = Cast<AEnemyCharacterBase>(Controller->GetPawn());

	FString MName = "Hit";
	if (Enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Enemy->GetMontage()[MName]) && !Enemy->GetHitCheck())
	{

		Enemy->SetHitCheck(true);
	}
	//Enemy->GetMesh()->GetAnimInstance()->StopAllMontages(1.0f);
	Controller->StopMovement();
	Enemy->PlayMontage(Enemy->GetMontage()[MName]);

	return EBTNodeResult::Succeeded;
}
