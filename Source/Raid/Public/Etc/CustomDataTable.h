// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomDataTable.generated.h"




UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	EQUIP = 1 UMETA(DisplayName = "Equip"),
	POTION = 2 UMETA(DisplayName = "Potion"),
	MATERIAL = 3 UMETA(DisplayName = "Material"),
	USEMATERIAL = 4 UMETA(DisplayName = "UseMaterial")
};

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	HAT = 1 UMETA(DisplayName = "Hat"),
	TOP = 2 UMETA(DisplayName = "Top"),
	WEAPON = 3 UMETA(DisplayName = "Weapon"),
	BOTTOM = 4 UMETA(DisplayName = "Bottom"),
	GLOVES = 5 UMETA(DisplayName = "Gloves")
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	CHAIN = 1 UMETA(DisplayName = "Chain"),
	ULTI = 2 UMETA(DisplayName = "Ulti"),
	NORMAL = 3 UMETA(DisplayName = "Normal"),

};

USTRUCT(BlueprintType)
struct FItemResourceData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemResourceData() : 
		Count(1), ItemImage(), ItemType(EItemType::NONE), Iid(0) ,EquipType(EEquipType::NONE){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Iid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EEquipType EquipType;

};

USTRUCT(BlueprintType)
struct FSkillResourceData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSkillResourceData() :
		Count(1), SkillImage(), SkillType(ESkillType::NONE), SkillName(TEXT("skill")),SkillTypeName(TEXT("SkillName")) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UTexture2D* SkillImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESkillType SkillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString SkillTypeName;

};

UCLASS()
class RAID_API ACustomDataTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomDataTable();


};
