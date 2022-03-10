// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

#include <Kismet/GameplayStatics.h>

#include <Engine/DataTable.h>

#include <Raid/Public/Effect/BladeSwipeEffect.h>
#include <Raid/Public/Effect/BladeUltimate.h>
#include <Raid/Public/UI/DamageText.h>
#include <Raid/Public/Etc/SkillData.h>
#include <Raid/Public/Etc/CharacterDamageType.h>
#include <Raid/Public/UI/SlotWidget.h>
#include <Raid/Public/UI/GameUI.h>
#include <Raid/Public/Interactive_Object/Interactive_Actor.h>

#include <Kismet/KismetMathLibrary.h>

#include "MyCharacter.generated.h"

DECLARE_DELEGATE(Fdele_Single);

UENUM()
enum class ECharacterState : uint8
{
	IDLE UMETA(DisplayName = "IDLE"),
	ATTACK UMETA(DisplayName = "ATTACK"),
	ABNORMAL UMETA(DisplayName = "ABNORMAL")
};

USTRUCT(Atomic,BlueprintType)
struct FSkillData1 : public FTableRowBase
{
	GENERATED_BODY()
public:
	FSkillData1()
		:AnimMontage(nullptr), Name(TEXT("")), Texture(nullptr), Damage(0), Cool(0), Mana(0), Delay(0)
	{};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Cool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Mana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Delay;
};

UCLASS(Abstract,Blueprintable, BlueprintType)
class RAID_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(const FObjectInitializer& ObjectInitializer);






	UFUNCTION(BlueprintCallable)
		void AnimMontagePlay();

		virtual void DashAnimMontagePlay();

	UFUNCTION(BlueprintCallable)
		void QSkillAnimMontagePlay();
	UFUNCTION(BlueprintCallable)
		void FalldownAnimMontagePlay();
	UFUNCTION(BlueprintCallable)
		void DodgeAnimMontagePlay();
	UFUNCTION(BlueprintCallable)
		void UltimateAnimMontagePlay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Hp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 FullHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Armor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32  Exp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 Mp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 FullMp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UFUNCTION()
		void MpRegen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAttackable;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bClickAttack;
	Fdele_Single Fuc_Attack;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UDataTable* SkillDataTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		TArray<FSkillData1> PlayerSkill;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* DashMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* DashAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* FalldownMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* DodgeMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* UltimateMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
		float QSkillCool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
		float UltiCool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
		float DashCool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
		float DodgeCool;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive", meta = (AllowPrivateAccess = "true"))
		class AInteractive_Actor* InteractiveActor;

	ECharacterState CSTATE;

	bool Infinity = false;
	bool Stop = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* RpgCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* RpgCameraSpringArmComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> QSkillEffectCol;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> UltimateEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<class UUserWidget> DamageWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class UDamageText* DamageWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<class UUserWidget> GameUIWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class UGameUI* GameUIWidget;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 Attackindex;

	
protected:
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:

	virtual void SetSkill();

	float GetQCool();

	float GetDodgeCool();
	
	virtual float GetDashCool();
	
	float GetUltiCool();

	float GetMaxHp();

	float GetCurrentHp();

	float GetMaxMp();

	float GetCurrentMp();

	void AttackAble(bool enable);

	void ForwardMove(float deltaTime, float speed);

	void SetAttackIndex(int32 index);

	void SetInfinity(bool enable);

	int32 GetAttackIndex();

	bool GetAttackable();

	void SwapSkill(int from, int to);

	ECharacterState GetState();

	FSkillData1 GetSkillData(int num);

	void SetState(ECharacterState state);

	void IdleState();

	void SkillEffect(FSkillData1* _skill);

	void InputAttackPressed();

	void InputAttackReleased();

	void UltimateAttack();

	AInteractive_Actor* GetInteractiveActor() { return InteractiveActor; }

	void SetInteractiveActor(class AInteractive_Actor* _actor) { InteractiveActor = _actor; }


	void SetStop(bool _stop);

	void SetAttackBox(bool enable);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetWidgetClass(){}

	class UGameUI* GetUI() { return GameUIWidget; }



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* AttackBox1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BlueprintWidget, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<class UUserWidget> InvenClass;

private:

	

};
