// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Raid/Public/UI/SlotWidget.h>
#include "Blueprint/DragDropOperation.h"
#include "DragDropWidget.generated.h"


/**
 * 
 */
UCLASS()
class RAID_API UDragDropWidget : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UDragDropWidget();

	void SetPayLoad(UObject* _load);

	UPROPERTY(EditAnywhere)
		class UProgressBar* Bar;

	UPROPERTY(EditAnywhere)
		class USlotWidget* Slot;

	int SlotNum;
	ESlotState SlotState;
	int32 ItemId;
	UTextBlock* ItemNum;


protected:
	UObject* Load;

};
