// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EquipmentUI.h"

#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>

#include <Kismet/GameplayStatics.h>

#include <Raid/Public/UI/SlotWidget.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/Etc/PNGameInstance.h>

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
