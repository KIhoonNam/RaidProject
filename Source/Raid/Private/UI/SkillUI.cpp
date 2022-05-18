// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillUI.h"



#include <Kismet/GameplayStatics.h>

#include <Components/ListView.h>

void USkillUI::NativeConstruct()
{
	Super::NativeConstruct();


}

void USkillUI::Init()
{
	UPNGameInstance* PNGameInstance = Cast<UPNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == PNGameInstance) return;


	auto CurrentItemData = NewObject<UPNGameInstance>(PNGameInstance);
		
	SkillList->AddItem(CurrentItemData);
}