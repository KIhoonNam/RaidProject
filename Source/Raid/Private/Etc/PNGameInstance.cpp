// Fill out your copyright notice in the Description page of Project Settings.


#include "Etc/PNGameInstance.h"

#include <Engine/DataTable.h>

#include <Etc/CustomDataTable.h>

UPNGameInstance::UPNGameInstance()
{
	FString ItemResourceDataPath = TEXT("DataTable'/Game/Datatable/ItemTable.ItemTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*ItemResourceDataPath);
	if (DT_ABCHARACTER.Succeeded())
	{
		ItemResourceData = DT_ABCHARACTER.Object;
	}
}

//FItemResourceData* UPNGameInstance::GetItemResourceDatas()
//{
//	return  ItemResourceData;
//}

FItemResourceData* UPNGameInstance::GetItemResourceData(int32 Iid)
{
	return  ItemResourceData->FindRow<FItemResourceData>(*FString::FromInt(Iid), TEXT(""));;
}
