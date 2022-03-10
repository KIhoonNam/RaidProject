// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillItemWidget.h"
#include <Blueprint/WidgetTree.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Components/Image.h>
#include <Raid/Public/UI/DragDropWidget.h>
#include <Raid/Public/UI/SlotWidget.h>

void USkillItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void USkillItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void USkillItemWidget::Init()
{
	Slot.Init(nullptr, 8);
	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);

	USlotWidget* Slots;
	int i = 0;
	for (auto widget : widgets)
	{
		Slots = Cast<USlotWidget>(widget);

		if (!Slots) continue;
		
		Slots->SetPlayer(this->Player);
		Slots->SetController(this->Controller);
		Slots->SetNum(i);
		Slots->SkillInit();
		Slot[Slots->GetNum()] = Slots;

		i++;

	}
}
