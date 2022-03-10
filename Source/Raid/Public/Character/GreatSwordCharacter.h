// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GreatSwordCharacter.generated.h"

class AWayPoint;

UCLASS()
class RAID_API AGreatSwordCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Hp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	// Sets default values for this character's properties
	AGreatSwordCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AWayPoint* NextWayPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool Attack = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayPattonMontage();
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> PattonOneEffect;
	
	UFUNCTION()
		void PattonOne();


	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<class UUserWidget> DamageWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class UDamageText* DamageWidget;
};
