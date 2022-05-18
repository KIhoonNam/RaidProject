// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillListView.h"

#include <Raid/Public/UI/SlotWidget.h>
#include <Raid/Public/Etc/PNGameInstance.h>

#include <Kismet/GameplayStatics.h>

#include <Components/TextBlock.h>
#include <Components/Border.h>



void USkillListView::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillListView::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UPNGameInstance* PNGameInstance = Cast<UPNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == PNGameInstance) return;

	auto CurrentItemData = PNGameInstance->GetSkillData();
}

void USkillListView::NativeOnItemSelectionChanged(bool bIsSelected)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("HI"));
}
