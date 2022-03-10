// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyCharactermeleeAnimNotifyState.generated.h"

class AMyCharacter;
class AMyPlayerController;
/**
 * 
 */
UCLASS()
class RAID_API UMyCharactermeleeAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	
private:
	int32 PrevAttackindex = 0;
	bool call;
	AMyCharacter* Player;
	AMyPlayerController* Controll;
	FHitResult Hit;
};
