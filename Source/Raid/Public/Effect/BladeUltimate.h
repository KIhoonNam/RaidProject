// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "BladeUltimate.generated.h"

UCLASS()
class RAID_API ABladeUltimate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABladeUltimate();

	UPROPERTY(VisibleAnywhere)
		uint32 Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* Particle;
	UFUNCTION()
		void SetBeginOverlap();



	UFUNCTION()
		void OnPlayerEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float time;
	
	bool OneHit;
};
