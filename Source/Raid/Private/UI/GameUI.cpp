// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI.h"
#include <Raid/Public/UI/HealthBarWidget.h>
#include <Raid/Public/UI/SkillItemWidget.h>
#include <Raid/Public/UI/InventoryUI.h>
#include <Raid/Public/UI/EquipmentUI.h>
#include <Raid/Public/Character/MyCharacter.h>




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
		Inven->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Equipment)
	{
		Equipment->SetPlayer(this->Player);
		Equipment->SetController(this->Controller);
		Equipment->Init();
		Equipment->SetVisibility(ESlateVisibility::Collapsed);

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
		if(Inven->GetVisibility() == ESlateVisibility::Collapsed)
			Inven->SetVisibility(ESlateVisibility::Visible);
		else if (Inven->GetVisibility() == ESlateVisibility::Visible)
			Inven->SetVisibility(ESlateVisibility::Collapsed);
		break;

	case EUIVisible::Equipment:
		if (Equipment->GetVisibility() == ESlateVisibility::Collapsed)
			Equipment->SetVisibility(ESlateVisibility::Visible);
		else if (Equipment->GetVisibility() == ESlateVisibility::Visible)
			Equipment->SetVisibility(ESlateVisibility::Collapsed);
	default:
		break;
	}
}

void UGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}
