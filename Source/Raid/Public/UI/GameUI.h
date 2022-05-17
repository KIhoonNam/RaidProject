// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUI.h"
#include "GameUI.generated.h"
class AMyCharacter;
class AMyPlayerController;
class USkillItemWidget;
class UHealthBarWidget;
class UInventoryUI;
class UEquipmentUI;
class USkillUI;
/**
* 
 * 
 */


UENUM()
enum class EUIVisible : uint8
{
	Inventory UMETA(DisplayName = "Inventory"),
	Equipment UMETA(DisplayName = "ATTACK"),
	Skill UMETA(DisplayName = "SKLL"),
	ABNORMAL UMETA(DisplayName = "ABNORMAL")
};


UCLASS()
class RAID_API UGameUI : public UCustomUI
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta = (BindWidget))
		USkillItemWidget* Skill;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UHealthBarWidget* State;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UInventoryUI* Inven;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UEquipmentUI* Equipment;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		USkillUI* Skill_UI;
	void Init() override;

	void UpdateSkill();

	UEquipmentUI* GetEquipment();

	UInventoryUI* GetInventory();

	void SetUIVisible(EUIVisible _uivisible);
	
	virtual void NativeConstruct() override;

	virtual void SetPlayer(AMyCharacter* _player) { Player = _player; }
	virtual void SetController(AMyPlayerController* _controller) { Controller = _controller; }




protected:
	AMyCharacter* Player;
	AMyPlayerController* Controller;
private:

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
