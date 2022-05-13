// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUI.h"
#include "SlotWidget.generated.h"

class UEquipmentUI;
class UInventoryUI;
class AMyCharacter;
struct FItemResourceData;

UENUM(BlueprintType)
enum class ESlotState : uint8
{
	ITEM UMETA(DisplayName = "ITEM"),
	SKILL UMETA(DisplayName = "SKILL"),
	EQUIPMENT UMETA(DisplayName = "Equipment")
};
/**
 * 
 */
UCLASS(Blueprintable)
class RAID_API USlotWidget : public UCustomUI
{
	GENERATED_BODY()

public:
	void SetNum(int _slotnum) { SlotNum = _slotnum; }
	int GetNum() { return SlotNum; }
	FItemResourceData* GetSlotData(){ return SlotData; }

	void SkillInit();
	void ItemInit(FItemResourceData* _data,UInventoryUI* _inven);
	void EquipmentInit(FItemResourceData* _data,UEquipmentUI* _equip);
	void SetSlotState(ESlotState _slotstate) { SlotState = _slotstate; }


	ESlotState GetSlotState() { return SlotState; }
protected:
	FString CoolSecondText = "s";
	FString CoolMinuteText = "m";
private:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnInitialized() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent)override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	//virtual FReply NativeOnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	ESlotState SlotState;

	UPROPERTY(EditAnywhere)
		int SlotNum;
	UPROPERTY(VisibleAnywhere,  meta = (BindWidget))
		class UProgressBar* SkillBar;
	UPROPERTY(VisibleAnywhere,  meta = (BindWidget))
		class UTextBlock* CoolTime;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* ItemNum;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UBorder* Bording;
	UPROPERTY(VisibleAnywhere)
		class UInventoryUI* Inven;
	UPROPERTY(VisibleAnywhere)
		class UEquipmentUI* Equip;
	UPROPERTY(EditAnywhere)
		int32 ItemId;
	//UPROPERTY(VisibleAnywhere)
	 FItemResourceData* SlotData;

	 

	void ItemRefresh(FItemResourceData* _data);
	void Equipmounting(UEquipmentUI* _equip);

	void EquipRelease(UInventoryUI* _inven);

	FEventReply OnMouseMove(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	
		



};
