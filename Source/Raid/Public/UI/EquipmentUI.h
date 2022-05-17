// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CustomUI.h"
#include "EquipmentUI.generated.h"

class UVerticalBoxSlot;
class USlotWidget;
class AMyCharacter;
/**
 * 
 */
UCLASS()
class RAID_API UEquipmentUI : public UCustomUI
{
	GENERATED_BODY()
public:
	void Init() override;



	TArray<USlotWidget*> GetSlot();
	void SetSlot(USlotWidget* _slot,int _num);

	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UVerticalBox* EquipBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<USlotWidget*> Slots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class UVerticalBoxSlot*> VerticalSlot;
private:
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
