// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillListView.h"


#include <Components/TextBlock.h>
#include <Components/Border.h>
#include <Raid/Public/UI/SlotWidget.h>


void USkillListView::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillListView::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("HI"));
}

void USkillListView::NativeOnItemSelectionChanged(bool bIsSelected)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("HI"));
}
