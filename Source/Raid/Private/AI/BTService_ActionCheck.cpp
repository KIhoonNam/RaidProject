// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_ActionCheck.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>
UBTService_ActionCheck::UBTService_ActionCheck()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("AttackCheck");
}

void UBTService_ActionCheck::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);


	auto Controller = owner_comp.GetAIOwner();

	auto const Enemy = Cast<AEnemyCharacterBase>(Controller->GetPawn());




	Controller->GetBlackboardComponent()->SetValueAsBool(bb_Keys::attack_check, montage_has_finished(Enemy));
	Enemy->SetEnemyType(EEnemyType::IDLE);

}

bool UBTService_ActionCheck::montage_has_finished(AEnemyCharacterBase* const Enemy)
{
	for (auto i : Enemy->GetMontage())
	{
		if (!Enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(i.Value))
			return false;
	}
	return true;
	
}
