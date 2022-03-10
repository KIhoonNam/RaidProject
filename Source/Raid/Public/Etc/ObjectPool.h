// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPool.generated.h"


class AEnemyIggyCharacter;
class AEnemyRampageCharacter;

UCLASS()
class RAID_API AObjectPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<AEnemyIggyCharacter> Iggy;
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<AEnemyRampageCharacter> Rampage;

	UPROPERTY()
		TArray<class AEnemyCharacterBase*> EnemyPool;


	int MonsterCount;

	float time;

	bool SpawnCheck;
		
};
