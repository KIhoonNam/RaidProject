// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EquipmentUI.h"

#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>

#include <Blueprint/WidgetBlueprintLibrary.h>

#include <Kismet/GameplayStatics.h>

#include <Raid/Public/UI/SlotWidget.h>
#include <Raid/Public/Character/MyCharacter.h>
//#include <Raid/Public/Etc/PNGameInstance.h>
#include <Raid/Public/UI/DragDropWidget.h>

TArray<USlotWidget*> UEquipmentUI::GetSlot()
{
	return Slots;
}

void UEquipmentUI::SetSlot(USlotWidget* _slot,int _num)
{

}

void UEquipmentUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEquipmentUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UEquipmentUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UEquipmentUI::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropWidget* WidgetDD = Cast<UDragDropWidget>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropWidget::StaticClass()));

	if (WidgetDD == nullptr) return;
	//WidgetDD->Offset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition() + FVector2D(50.0f,50.0f));




	WidgetDD->DragPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	WidgetDD->DefaultDragVisual = this;
	WidgetDD->Pivot = EDragPivot::MouseDown;
	WidgetDD->ParentWidget = this->GetParent();
	WidgetDD->CurrentWidget = this;

	OutOperation = WidgetDD;;

	this->RemoveFromParent();

	//	this->SetVisibility(ESlateVisibility::Collapsed);
}
FReply UEquipmentUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{

		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	}

	return reply.NativeReply;
}

void UEquipmentUI::Init()
{
	Slots.Init(nullptr, 12);
	VerticalSlot.Init(nullptr, 12);

	UPNGameInstance* PNGameInstance = Cast<UPNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == PNGameInstance) return;

	for (int i = 0; i < Slots.Num(); i++)
	{
		auto CurrentItemData = PNGameInstance->GetItemResourceData(0);

		Slots[i] = CreateWidget<USlotWidget>(GetWorld(), Player->InvenClass);

		Slots[i]->SetNum(i);
		Slots[i]->SetPlayer(this->Player);
		Slots[i]->SetController(this->Controller);
		Slots[i]->EquipmentInit(nullptr,this);
		Slots[i]->Padding.Top = 20;

		if (i < 6)
		{
			VerticalSlot[i] = EquipBox->AddChildToVerticalBox(Slots[i]);
		}
	}
}
