// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_HitCheck.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UAnimNotify_HitCheck : public UAnimNotify
{
	GENERATED_BODY()
private:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	class AEnemyCharacterBase* Player;
	class AEnemyControllerBase* EnemyController;
};
