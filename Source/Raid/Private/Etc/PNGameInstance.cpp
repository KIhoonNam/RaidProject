// Fill out your copyright notice in the Description page of Project Settings.


#include "Etc/PNGameInstance.h"





UPNGameInstance::UPNGameInstance()
{
	FString ItemResourceDataPath = TEXT("DataTable'/Game/Datatable/ItemTable.ItemTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*ItemResourceDataPath);
	if (DT_ABCHARACTER.Succeeded())
	{
		ItemResourceData = DT_ABCHARACTER.Object;
	}

	FString SkillResourceDataPath = TEXT("DataTable'/Game/Datatable/SkillTable.SkillTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SABCHARACTER(*SkillResourceDataPath);
	if (DT_SABCHARACTER.Succeeded())
	{
		SkillResourceData = DT_SABCHARACTER.Object;
	}

}

//FItemResourceData* UPNGameInstance::GetItemResourceDatas()
//{
//	return  ItemResourceData;
//}

FItemResourceData* UPNGameInstance::GetItemResourceData(int32 Iid)
{
	return  ItemResourceData->FindRow<FItemResourceData>(*FString::FromInt(Iid), TEXT(""));
}

FSkillResourceData* UPNGameInstance::GetSkillResourceData(int32 Iid)
{
	return SkillResourceData->FindRow<FSkillResourceData>(*FString::FromInt(Iid), TEXT(""));
}
