// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GreatSwordAIController.generated.h"

class AGreatSwordCharacter;

/**
 * 
 */
UCLASS()
class RAID_API AGreatSwordAIController : public AAIController
{
	GENERATED_BODY()
private:
	AGreatSwordAIController();
	
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSecond) override;

	virtual FRotator GetControlRotation() const override;

	void MonsterAttack();

	AGreatSwordCharacter* Character;

	AActor* Target;

	FTimerHandle timer;
	
	FRotator Distance;
	FRotator Direct;

	bool TimerStop = false;

public:
	UFUNCTION()
		void OnSenseUpdated(const TArray<AActor*>& DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIAttackRadius = 400.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightAge = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistancePlayer;

	
};
