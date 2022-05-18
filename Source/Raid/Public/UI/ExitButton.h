// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CustomUI.h"
#include "ExitButton.generated.h"

class UBorder;
/**
 * 
 */
UCLASS()
class RAID_API UExitButton : public UCustomUI
{
	GENERATED_BODY()
public:

private:



	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(EditAnywhere)
	bool ButtonCasting = false;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		UBorder* ExitButton;
};
