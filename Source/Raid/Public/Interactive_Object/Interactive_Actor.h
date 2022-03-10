// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include <Components/WidgetComponent.h>

#include <Raid/Public/Controller/MyPlayerController.h>
#include <Raid/Public/Character/MyCharacter.h>

#include <Blueprint/UserWidget.h>

#include <Kismet/GameplayStatics.h>


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive_Actor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class AMyPlayerController;
class AMyCharacter;

UCLASS()
class RAID_API AInteractive_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractive_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		TSubclassOf<class UUserWidget> WidgetClass;


	//UFUNCTION()
	//virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 각 상호작용 실행
	virtual void RunInteractive();

	

};
