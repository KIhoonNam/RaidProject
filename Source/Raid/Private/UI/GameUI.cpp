// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI.h"
#include <Raid/Public/UI/HealthBarWidget.h>
#include <Raid/Public/UI/SkillItemWidget.h>
#include <Raid/Public/UI/InventoryUI.h>
#include <Raid/Public/UI/EquipmentUI.h>
#include <Raid/Public/UI/DragDropWidget.h>
#include <Raid/Public/UI/SkillUI.h>
#include <Raid/Public/Character/MyCharacter.h>



#include <Blueprint/DragDropOperation.h>
#include <Blueprint/WidgetTree.h>






void UGameUI::Init()
{
	Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (State)
	{
		State->SetPlayer(this->Player);
		State->SetController(this->Controller);
	}

	if (Skill)
	{
		Skill->SetPlayer(this->Player);
		Skill->SetController(this->Controller);
		Skill->Init();
	}

	if (Inven)
	{
		Inven->SetPlayer(this->Player);
		Inven->SetController(this->Controller);
		Inven->Init();
		Inven->GetRootWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Equipment)
	{
		Equipment->SetPlayer(this->Player);
		Equipment->SetController(this->Controller);
		Equipment->Init();
		Equipment->GetRootWidget()->SetVisibility(ESlateVisibility::Collapsed);

	}

	if (Skill_UI)
	{
		Skill_UI->SetPlayer(this->Player);
		Skill_UI->SetController(this->Controller);
		Skill_UI->Init();
		Skill_UI->GetRootWidget()->SetVisibility(ESlateVisibility::Collapsed);

	}
}

void UGameUI::UpdateSkill()
{
	Skill->Init();
}

UEquipmentUI* UGameUI::GetEquipment()
{
	return Equipment;
}

UInventoryUI* UGameUI::GetInventory()
{
	return Inven;
}

void UGameUI::SetUIVisible(EUIVisible _uivisible)
{
	switch (_uivisible)
	{
	case EUIVisible::Inventory:
		if(Inven->GetRootWidget()->GetVisibility() == ESlateVisibility::Collapsed)
			Inven->GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
		else if (Inven->GetRootWidget()->GetVisibility() == ESlateVisibility::Visible)
			Inven->GetRootWidget()->SetVisibility(ESlateVisibility::Collapsed);
		break;

	case EUIVisible::Equipment:
		if (Equipment->GetRootWidget()->GetVisibility() == ESlateVisibility::Collapsed)
			Equipment->GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
		else if (Equipment->GetRootWidget()->GetVisibility() == ESlateVisibility::Visible)
			Equipment->GetRootWidget()->SetVisibility(ESlateVisibility::Collapsed);
	case EUIVisible::Skill:
		if (Skill_UI->GetRootWidget()->GetVisibility() == ESlateVisibility::Collapsed)
			Skill_UI->GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
		else if (Skill_UI->GetRootWidget()->GetVisibility() == ESlateVisibility::Visible)
			Skill_UI->GetRootWidget()->SetVisibility(ESlateVisibility::Collapsed);
	default:
		break;
	}
}

void UGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

bool UGameUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropWidget* oper = Cast<UDragDropWidget>(InOperation);

	if (oper == NULL) return false;

	oper->CurrentWidget->AddToViewport();


	FVector2D NewPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition()) - oper->DragPosition;
	oper->CurrentWidget->SetPositionInViewport(NewPosition, false);

	return true;
}
