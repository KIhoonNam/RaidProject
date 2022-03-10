// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "GreatBurstEffect.generated.h"

class AGreatSwordCharacter;

UCLASS()
class RAID_API AGreatBurstEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	AGreatBurstEffect();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* Particle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
		uint32 Damage;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamage(float damage);

	UFUNCTION()
		void SetBeginOverlap(AActor* actor);
	UFUNCTION()
		void OnPlayerEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	AActor* Character;

	
private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		 TSubclassOf<UDamageType> ChDamageType;
	float time;
};
