// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTService_MeleeAttack.h"

#include <Raid/Public/Controller/EnemyControllerBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

UMyBTService_MeleeAttack::UMyBTService_MeleeAttack()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("IsMeleeRange");
}

void UMyBTService_MeleeAttack::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	auto const controll = owner_comp.GetAIOwner();

	auto const Enemy = Cast<AEnemyCharacterBase>(controll->GetPawn());

	auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	float Distance = Enemy->GetDistanceTo(Player);
	bool Bool = Distance <= Meleerange;
	//if(montage_has_finished(Enemy))
	controll->GetBlackboardComponent()->SetValueAsBool(bb_Keys::player_is_in_melee_range,
		Distance <= Meleerange);

	if (controll->GetBlackboardComponent()->GetValueAsBool(bb_Keys::player_is_in_melee_range))
	{
		Enemy->SetEnemyType(EEnemyType::IDLE);
		controll->StopMovement();
	}

}

bool UMyBTService_MeleeAttack::montage_has_finished(AEnemyCharacterBase* const Enemy)
{
	for (auto i : Enemy->GetMontage())
	{
		if (!Enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(i.Value))
			return false;
	}
	return true;
}
