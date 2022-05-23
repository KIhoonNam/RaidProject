// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SlotWidget.h"
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>
#include <Components/Border.h>

#include <Engine/Texture2D.h>


#include <Blueprint/WidgetBlueprintLibrary.h>

#include <Raid/Public/UI/DragDropWidget.h>
#include <UI/InventoryUI.h>
#include <UI/EquipmentUI.h>
#include <Raid/Public/Character/MyCharacter.h>
//#include <Raid/Public/Etc/CustomDataTable.h>
FReply USlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	Controller->SetUIEnable(true);
	if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{

		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		
	}
	else if (InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{

		if(SlotState != ESlotState::SKILL && SlotData != nullptr)
		switch (SlotData->ItemType)
		{
		case EItemType::EQUIP:
			{
			if (SlotState == ESlotState::ITEM)
				Equipmounting(Player->GetUI()->GetEquipment());
			else if (SlotState == ESlotState::EQUIPMENT)
				EquipRelease(Player->GetUI()->GetInventory());
			break;
			}
		default:
			break;
		}
	}
	return reply.NativeReply;
}


void USlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (this->SkillBar->WidgetStyle.BackgroundImage.GetResourceObject() != nullptr)
	{
		UDragDropWidget* WidgetDD = Cast<UDragDropWidget>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropWidget::StaticClass()));

		if (WidgetDD == nullptr) return;
		//WidgetDD->Offset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition() + FVector2D(50.0f,50.0f));
		OutOperation = WidgetDD;;

		WidgetDD->SlotNum = this->SlotNum;
		WidgetDD->Bar = this->SkillBar;
		WidgetDD->Slot = this;
		WidgetDD->Slot->SetVisibility(ESlateVisibility::HitTestInvisible);
		WidgetDD->SlotState = SlotState;
		WidgetDD->DefaultDragVisual = this;
		WidgetDD->Pivot = EDragPivot::MouseDown;
		if (WidgetDD->SlotState == ESlotState::ITEM)
		{
			WidgetDD->ItemId = this->ItemId;
			WidgetDD->ItemNum = this->ItemNum;
		}
	}
}

bool USlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	Controller->SetUIEnable(false);
	UDragDropWidget* oper = Cast<UDragDropWidget>(InOperation);
	oper->Slot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (oper != nullptr && SlotState == oper->SlotState)
	{
		if (SlotState == ESlotState::ITEM)
		{
			Inven->SwapItem(oper->SlotNum, this->SlotNum);

		}
		else if (SlotState == ESlotState::SKILL)
		{
			
		}
		return true;

	}

	return false;
}

void USlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	UDragDropWidget* oper = Cast<UDragDropWidget>(InOperation);
	Controller->SetUIEnable(false);
	oper->Slot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

}

FReply USlotWidget::NativeOnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonUp(MyGeometry, MouseEvent);


	if (MouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{
		

	}
	else if (MouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{
		Controller->SetUIEnable(false);

	}
	return reply.NativeReply;
}

FReply USlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);


	if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{


	}
	else if (InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{
	

	}
	return reply.NativeReply;
}



FEventReply USlotWidget::OnMouseMove(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	FEventReply Reply;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("MOVE"));
	}

	return Reply;
}

void USlotWidget::SkillInit()
{
	SlotState = ESlotState::SKILL;


	switch (SlotNum)
	{
	case 0:
		if (Player->GetSkillData(0).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(0).Texture);		
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	case 1:
		if (Player->GetSkillData(1).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(1).Texture);
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	case 2:
		if (Player->GetSkillData(2).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(2).Texture);
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	case 3:
		if (Player->GetSkillData(3).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(3).Texture);
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	case 4:
		if (Player->GetSkillData(4).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(3).Texture);
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	case 5:
		if (Player->GetSkillData(5).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(3).Texture);
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	case 6:
		if (Player->GetSkillData(6).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(3).Texture);
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	case 7:
		if (Player->GetSkillData(7).Texture != nullptr)
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(Player->GetSkillData(3).Texture);
		else
			SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		return;
	}
}

void USlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (ClickTime > 0.1f)
	{
		Controller->SetUIEnable(false);
		ClickTime = 0;
	}
	if(Controller->GetUIEnable())
		ClickTime += InDeltaTime;
	if (SlotState == ESlotState::SKILL && Player != NULL)
	{
		switch (SlotNum)
		{
		case 0:
			if (Player->GetQCool() > 0)
			{
				SkillBar->SetPercent(Player->GetSkillData(0).Cool / 8.0f);
				CoolTime->SetText(FText::FromString(FString::FromInt(Player->GetQCool())));
				CoolTime->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				CoolTime->SetVisibility(ESlateVisibility::Collapsed);
			}
			return;
		case 1:
			if (Player->GetDashCool() > 0)
			{
				SkillBar->SetPercent(Player->GetSkillData(1).Cool / 8.0f);
				CoolTime->SetText(FText::FromString(FString::FromInt(Player->GetDashCool())));
				CoolTime->SetVisibility(ESlateVisibility::Collapsed);
			}
			return;
		case 2:
			if (Player->GetDodgeCool() > 0)
			{
				SkillBar->SetPercent(Player->GetSkillData(2).Cool / 10.0f);
				CoolTime->SetText(FText::FromString(FString::FromInt(Player->GetDodgeCool())));
				CoolTime->SetVisibility(ESlateVisibility::Collapsed);
			}
			return;
		case 3:
			if (Player->GetUltiCool() > 0)
			{
				SkillBar->SetPercent(Player->GetSkillData(3).Cool / 300.0f);
				CoolTime->SetText(FText::FromString(FString::FromInt(Player->GetUltiCool())));
				CoolTime->SetVisibility(ESlateVisibility::Collapsed);
			}
			return;
		case 4:
			return;
		case 5:
			return;
		case 6:
			return;
		case 7:
			return;

		}
	}


}


void USlotWidget::ItemInit(FItemResourceData* _data, UInventoryUI* _inven)
{
	SlotState = ESlotState::ITEM;
	Inven = _inven;

	ItemRefresh(_data);
}

void USlotWidget::EquipmentInit(FItemResourceData* _data,UEquipmentUI* _equip)
{
	SlotState = ESlotState::EQUIPMENT;
	Equip = _equip;

	ItemRefresh(_data);
}

void USlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Bording->OnMouseMoveEvent.BindDynamic(this, &USlotWidget::OnMouseMove);
}

void USlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Bording->Background.Margin = 0.013f;
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("MOVE"));
}

void USlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Bording->Background.Margin = 0.00f;
}

void USlotWidget::Equipmounting(UEquipmentUI* _equip)
{
	switch (SlotData->EquipType)
	{
	case EEquipType::TOP:
	{
		auto ChangeData = _equip->GetSlot()[1]->SlotData;
		auto CurrentData = SlotData;
		ItemRefresh(ChangeData);
		_equip->GetSlot()[1]->ItemRefresh(CurrentData);
		break;
	}
	default:
		break;
	}
}

void USlotWidget::ItemRefresh(FItemResourceData* _data)
{
	if (_data != nullptr)
	{
		ItemNum->SetText(FText::FromString(FString::FromInt(_data->Count)));
		ItemNum->SetVisibility(ESlateVisibility::HitTestInvisible);
		SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(_data->ItemImage);
		ItemId = _data->Iid;
		SlotData = _data;
	}
	else
	{
		ItemNum->SetVisibility(ESlateVisibility::Collapsed);
		SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(nullptr);
		ItemId = -1;
		SlotData = nullptr;
	}
}

void USlotWidget::EquipRelease(UInventoryUI* _inven)
{
	for (auto inslot : _inven->GetInvenSlot())
	{
		if (inslot->GetSlotData() == nullptr)
		{
			auto ChangeData = inslot->GetSlotData();
			auto CurrentData = SlotData;
			ItemRefresh(ChangeData);
			inslot->ItemRefresh(CurrentData);
		}
	}
}

void USlotWidget::SkillRefresh(FSkillResourceData* _data)
{
	Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ItemNum->SetVisibility(ESlateVisibility::Collapsed);
	SkillBar->WidgetStyle.BackgroundImage.SetResourceObject(_data->SkillImage);
	SlotState = ESlotState::SKILL;
	
}
