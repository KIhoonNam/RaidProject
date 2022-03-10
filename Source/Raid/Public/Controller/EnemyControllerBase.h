// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <Raid/Public/Etc/WayPoint.h>
#include <Perception/AIPerceptionComponent.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/Character/EnemyCharacterBase.h>
#include <Raid/Public/Etc/BlackBoard_Keys.h>

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

#include <Perception/AISenseConfig_Sight.h>

#include <Kismet/KismetMathLibrary.h>

#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BlackboardData.h>
#include <BehaviorTree/BlackboardComponent.h>


#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyControllerBase.generated.h"

class AEnemyCharacterBase;

/**
 * 
 */
UCLASS()
class RAID_API AEnemyControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyControllerBase();

	void SetCharacter(AEnemyCharacterBase* _character) { Character = _character; }
public:
	UFUNCTION()
		virtual void OnSenseUpdated(AActor* actor, FAIStimulus const Stimulus);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIAttackRadius = 400.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightAge = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 360.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistancePlayer;

	float HomeDistance;

	FVector HomeVector;
protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSecond) override;

	virtual FRotator GetControlRotation() const override;

	

	void MonsterAttack();

	UPROPERTY(VisibleAnywhere)
		class UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere)
		class UBlackboardData* BBAsset;

	UPROPERTY(VisibleAnywhere)
		class UBehaviorTreeComponent* BTComp;
	UPROPERTY(VisibleAnywhere)
		class UBlackboardComponent* BBComp;

public:

	UBlackboardComponent* GetBlackBoard() { return BBComp; }

	static const FName HomePosKey;
	static const FName TargetLocation;



	AEnemyCharacterBase* Character;

	AActor* Target;

	FTimerHandle timer;

	FRotator Distance;
	FRotator Direct;

	bool TimerStop = false;

};
