// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive_Object/Interactive_Actor.h"
#include "Interactive_ChaosMap.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API AInteractive_ChaosMap : public AInteractive_Actor
{
	GENERATED_BODY()
	
public:
	AInteractive_ChaosMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	 void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;
	UFUNCTION()
	 void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) ;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void RunInteractive() override;
};








