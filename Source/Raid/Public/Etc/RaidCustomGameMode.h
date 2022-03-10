// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RaidCustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API ARaidCustomGameMode : public AGameMode
{
	GENERATED_BODY()

	
public:
	ARaidCustomGameMode();
protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UUserWidget> PlayerHUDClass;
	UPROPERTY()
		class UUserWidget* CurrentWidget;
};
