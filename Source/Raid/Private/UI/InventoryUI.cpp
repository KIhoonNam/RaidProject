// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryUI.h"
#include <Raid/Public/UI/SlotWidget.h>
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/UI/DragDropWidget.h>
#include <Raid/Public/Etc/PNGameInstance.h>

#include <Components/UniformGridSlot.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/UniformGridPanel.h>

#include <Blueprint/DragDropOperation.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

#include <Kismet/GameplayStatics.h>

#include <Engine/Texture2D.h>

TArray<class USlotWidget*> UInventoryUI::GetInvenSlot()
{
	return SlotWidget;
}

void UInventoryUI::SwapItem(int32 _operNum, int32 _thisNum)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::FromInt(_operNum));

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::FromInt(_thisNum));
	

	

	USlotWidget* temp = SlotWidget[_operNum];

	SlotWidget[_operNum] = SlotWidget[_thisNum];

	SlotWidget[_thisNum] = temp;

	SlotWidget[_operNum]->SetNum(_operNum);
	SlotWidget[_thisNum]->SetNum(_thisNum);

	UUniformGridSlot* tempa = GridSlot[_operNum];

	GridSlot[_operNum] = GridSlot[_thisNum];

	GridSlot[_thisNum] = tempa;

	GridSlot[_operNum]->SetRow(_operNum / 7);
	GridSlot[_operNum]->SetColumn(_operNum % 7);

	GridSlot[_thisNum]->SetRow(_thisNum / 7);
	GridSlot[_thisNum]->SetColumn(_thisNum % 7);
}

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInventoryUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInventoryUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryUI::Init()
{
	SlotWidget.Init(nullptr, 56);
	GridSlot.Init(nullptr, 56);
	UPNGameInstance* PNGameInstance = Cast<UPNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == PNGameInstance) return;

	
	for (int i = 0; i < 56; i++)
	{
		auto Rand = FMath::RandRange(0, 9);
		auto CurrentItemData = PNGameInstance->GetItemResourceData(Rand);


		SlotWidget[i] = CreateWidget<USlotWidget>(GetWorld(), Player->InvenClass);

		SlotWidget[i]->SetNum(i);
		SlotWidget[i]->SetPlayer(this->Player);
		SlotWidget[i]->SetController(this->Controller);
		if (i == 55)
			SlotWidget[i]->ItemInit(nullptr, this);
		else
			SlotWidget[i]->ItemInit(CurrentItemData,this);
		

		GridSlot[i] = UniformGrid->AddChildToUniformGrid(SlotWidget[i]);

		if (GridSlot[i])
		{
			GridSlot[i]->SetRow(i / 7);
			GridSlot[i]->SetColumn(i%7);
		}
	}

	
}