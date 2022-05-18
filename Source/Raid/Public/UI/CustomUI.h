// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Raid/Public/Controller/MyPlayerController.h>
#include <Raid/Public/Etc/PNGameInstance.h>
#include "CustomUI.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UCustomUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Init(){}

	virtual void SetPlayer(class AMyCharacter* _player) { Player = _player; }
	virtual  void SetController(class AMyPlayerController* _controller) { Controller = _controller; }
	
protected:
	class AMyCharacter* Player;
	class AMyPlayerController* Controller;

	float ClickTime;

};
