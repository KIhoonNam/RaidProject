// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomUI.h"
#include "SkillItemWidget.generated.h"
class AMyCharacter;
class USlotWidget;
/**
 * 
 */
UCLASS()
class RAID_API USkillItemWidget : public UCustomUI
{
	GENERATED_BODY()
public:
	void Init() override;
protected:


	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry,float InDeltaTime) override;

	
private:
	TArray<USlotWidget*> Slot;
};
