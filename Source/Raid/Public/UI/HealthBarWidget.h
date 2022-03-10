// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUI.h"
#include "HealthBarWidget.generated.h"
class AMyCharacter;
/**
 * 
 */
UCLASS()
class RAID_API UHealthBarWidget : public UCustomUI
{
	GENERATED_BODY()

public:

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry,float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHealthLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHealthLabel;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ManaBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentManaLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxManaLabel;

	
private:
	/*virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;*/
};
