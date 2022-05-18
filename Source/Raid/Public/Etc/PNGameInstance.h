// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Engine/DataTable.h>
#include <Etc/CustomDataTable.h>
#include "PNGameInstance.generated.h"
struct FSkillResourceData;
struct FItemResourceData;
class UDataTable;
/**
 * 
 */
UCLASS()
class RAID_API UPNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPNGameInstance();
	/*TArray<FItemResourceData*> GetItemResourceDatas();*/
	FItemResourceData* GetItemResourceData(int32 Iid);
	FSkillResourceData* GetSkillResourceData(int32 Iid);
	UDataTable* GetSkillData() { return SkillResourceData; }

private:
	UPROPERTY()
		UDataTable* ItemResourceData;
	UPROPERTY()
		UDataTable* SkillResourceData;
};
