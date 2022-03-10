// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


class AMyCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	bool GetClickAttack();

	bool GetDashAttack();

	bool GetDashOne();

	bool GetUIEnable(){ return UIEnable; }

	void SetUIEnable(bool Enable) { UIEnable = Enable; }

	void SetAction(bool Enable);

	void SetClickDash(bool Enable);

	void SetMeleeRotation(AMyCharacter* pawn,FHitResult hit);

	void QSkill();

protected:
	virtual void BeginPlay() override;
	
	bool bClickMouse;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bClickAttack;

	bool bClickDash;

	bool bClickDodge;

	bool bClickQ;
	
	bool bAction;

	bool bClickUltimate;
	bool DashOne;
	void InputClickPressed();

	void InputClikReleased();

	void InputAttackPressed();

	void InputAttackReleased();

	void InputDashPressed();
	
	void InputDashReleased();

	void InputQPressed();

	void InputQReleased();

	void InputUltimateReleased();

	void InputUltimatePressed();

	void InputInventoryPressed();

	void InputInventoryReleased();

	void InputEquipmentPressed();

	void InputEquipmentReleased();

	void InputInteractivePressed();
	
	void InputInteractiveReleased();

	virtual void SetupInputComponent() override;

	void SetNewDestination(const FVector destination);

	void MoveToMouseCursor();

	void AttackRotation();

	void Dash();

	void Dodge();

	void Ultimate();
	

	virtual void PlayerTick(float DeltaTime) override;

	
private:
	AMyCharacter* m_Character;

	//class AAIController* Control;
	bool UIEnable;
	float DashCool;
	float DodgeCool;
	float QCool;
	float time;
	float UltiCool;
};
