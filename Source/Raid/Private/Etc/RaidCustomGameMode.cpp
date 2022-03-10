// Fill out your copyright notice in the Description page of Project Settings.


#include "Etc/RaidCustomGameMode.h"
#include <Components/WidgetComponent.h>
#include <Blueprint/UserWidget.h>



void ARaidCustomGameMode::BeginPlay()
{
	Super::BeginPlay();

	

	//if (PlayerHUDClass != NULL)
	//{
	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
	//	if (CurrentWidget != nullptr)
	//	{
	//		CurrentWidget->AddToViewport();
	//	}
	//}

}

ARaidCustomGameMode::ARaidCustomGameMode()
	:Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Character/BladeCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<AController> PlayerControllerClassFinder(TEXT("/Game/Character/MyMyPlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;

	
	

}
