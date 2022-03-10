// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive_Object/Interactive_ChaosMap.h"
#include <Kismet/GameplayStatics.h>


AInteractive_ChaosMap::AInteractive_ChaosMap()
{
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AInteractive_ChaosMap::OnBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AInteractive_ChaosMap::OnEndOverlap);

}

void AInteractive_ChaosMap::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractive_ChaosMap::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->ActorHasTag("Player"))
	{
		auto Player = Cast<AMyCharacter>(OtherActor);

		Player->SetInteractiveActor(this);
		
		Widget->SetVisibility(true);
	}
}

void AInteractive_ChaosMap::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor->ActorHasTag("Player"))
	{
		auto Player = Cast<AMyCharacter>(OtherActor);
		Player->SetInteractiveActor(nullptr);

		Widget->SetVisibility(false);
	}
}

void AInteractive_ChaosMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractive_ChaosMap::RunInteractive()
{
	UGameplayStatics::OpenLevel(this, TEXT("ChaosMap"));
}
