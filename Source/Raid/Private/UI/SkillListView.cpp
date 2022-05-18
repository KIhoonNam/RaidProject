// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillListView.h"

#include <Raid/Public/UI/SlotWidget.h>
//#include <Raid/Public/Etc/PNGameInstance.h>

#include <Kismet/GameplayStatics.h>

#include <Components/TextBlock.h>
#include <Components/Border.h>



void USkillListView::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillListView::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UPNGameInstance* PNGameInstance = Cast<UPNGameInstance>(ListItemObject);

	auto SetSkillmSource = PNGameInstance->GetSkillResourceData(0);

	if(SetSkillmSource != NULL)
	RefreshSkilitem(SetSkillmSource);


}

void USkillListView::NativeOnItemSelectionChanged(bool bIsSelected)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("HI"));
}

void USkillListView::RefreshSkilitem(FSkillResourceData* _data)
{

	SkillLevel->SetText(FText::FromString(FString::FromInt(_data->Count)));

	SkillName->SetText(FText::FromString(_data->SkillName));

	StateName->SetText(FText::FromString(_data->SkillTypeName));

	SlotWidget->SkillRefresh(_data);
}
