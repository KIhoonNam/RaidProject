// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Raid/Public/Etc/WayPoint.h>
#include <Raid/Public/Effect/GreatBurstEffect.h>
#include <Raid/Public/UI/DamageText.h>

#include <Components/WidgetComponent.h>

#include <Blueprint/UserWidget.h>

#include <Kismet/GameplayStatics.h>

#include <Engine/Public/TimerManager.h>

#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

class AWayPoint;



UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	IDLE = 0 UMETA(DisplayName = "Idle"),
	ATTACK = 1 UMETA(DisplayName = "Attack"),
	HIT = 2 UMETA(DisplayName = "Hit"),
	NEUTRALIZATION = 3 UMETA(DisplayName = "Neutralization"),
	MOVE = 4 UMETA(DisplayName = "Move")
};


UCLASS()
class RAID_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacterBase();

	AWayPoint* GetNextWayPoint() { return NextWayPoint; }
	void SetNextWayPoint(AWayPoint* _waypoint) { NextWayPoint = _waypoint; }

	bool GetAttack() { return Attack; }
	void SetAttack(bool _attack) { Attack = _attack; }

	TMap<FString, class UAnimMontage*> GetMontage() { return Montage; }


	EEnemyType GetEnemyType() { return EnemyType; }

	void SetEnemyType(EEnemyType _enemytype) { EnemyType = _enemytype; }

	virtual void PlayMontage(UAnimMontage* _montage);

	UFUNCTION(BlueprintCallable)
		bool GetHitCheck() { return HitCheck; }
	UFUNCTION(BlueprintCallable)
		void SetHitCheck(bool _hitcheck) { HitCheck = _hitcheck; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void OnConstruction(const FTransform& Transform)override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Hp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AWayPoint* NextWayPoint;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMesh* SkeletaMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString,class UAnimMontage*> Montage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class UMaterialInterface*> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class UMaterialInstanceDynamic*> DynamicMaterial;

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class UAnimInstance> AnimBP;

	UPROPERTY(EditAnywhere)
		bool HitCheck = false;

	EEnemyType EnemyType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool Attack = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float FadeOutScala = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool DeathCheck = false;
	FTimerHandle FadeHandle;
protected:
	virtual void FadeOutTimer();


public:	
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<class UUserWidget> DamageWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class UDamageText* DamageWidget;
};


