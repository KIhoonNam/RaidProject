// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CustomUI.h"
#include "InventoryUI.generated.h"


/**
 * 
 */
UCLASS()
class RAID_API UInventoryUI : public UCustomUI
{
	GENERATED_BODY()
public:
	void Init() override;

	TArray<class USlotWidget*> GetInvenSlot();

	void SwapItem(int32 _operNum, int32 _thisNum);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UUniformGridPanel* UniformGrid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class USlotWidget*> SlotWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class UUniformGridSlot*> GridSlot;

private:


	

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
