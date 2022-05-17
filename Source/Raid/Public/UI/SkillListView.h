// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UI/CustomUI.h"
#include "SkillListView.generated.h"

class UTextBlock;
class UBorder;
class USlotWidget;

/**
 * 
 */
UCLASS(Abstract)
class RAID_API USkillListView : public UCustomUI,public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// ������ UI ���� �� ȣ��

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	// ������ ���� �� ȣ��
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
private:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		 UBorder* Minus;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		 UBorder* Plus;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		 UTextBlock* SkillLevelName;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		 UTextBlock* SkillLevel;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		 UTextBlock* SkillName;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		 UTextBlock* StateName;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		 USlotWidget* SlotWidget;
};
