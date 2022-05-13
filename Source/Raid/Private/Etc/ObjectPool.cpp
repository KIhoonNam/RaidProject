// Fill out your copyright notice in the Description page of Project Settings.


#include "Etc/ObjectPool.h"

#include <Raid/Public/Character/EnemyIggyCharacter.h>
#include <Raid/Public/Character/EnemyRampageCharacter.h>

#include <Components/WidgetComponent.h>

#include <Blueprint/UserWidget.h>

#include <Kismet/GameplayStatics.h>

#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"

// Sets default values
AObjectPool::AObjectPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnCheck = false;

	time = 0.0f;

	MonsterCount = 0;

	 static ConstructorHelpers::FClassFinder<AEnemyIggyCharacter> IggyObject(TEXT("/Game/Character/BP_EnemyIggyCharacter"));
	 if (IggyObject.Succeeded())
	 {
		 Iggy = IggyObject.Class;
	 }

	 static ConstructorHelpers::FClassFinder<AEnemyRampageCharacter> RampageObject(TEXT("/Game/Character/BP_EnemyRampageCharacter"));
	 if (RampageObject.Succeeded())
	 {
		 Rampage = RampageObject.Class;
	 }
}

// Called when the game starts or when spawned
void AObjectPool::BeginPlay()
{
	Super::BeginPlay();


	for (int i = 0; i < 3; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		FVector SpawnLocation = GetActorLocation();
		FVector RandomSpawn = FVector(FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-200.0f, 200.0f),0.0f);
		FVector SpawnPoint = SpawnLocation + RandomSpawn;
		FRotator rotator;

		if (Rampage != nullptr && Iggy != nullptr)
		{	
			EnemyPool.Add(GetWorld()->SpawnActor<AEnemyIggyCharacter>(Iggy, SpawnPoint, rotator, SpawnParams));
			RandomSpawn = FVector(FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-200.0f, 200.0f), 0.0f);
			SpawnPoint = SpawnLocation + RandomSpawn;
			EnemyPool.Add(GetWorld()->SpawnActor<AEnemyRampageCharacter>(Rampage, SpawnPoint, rotator, SpawnParams));
		
		}
	}
	for (auto it : EnemyPool)
		if (it != nullptr)
		{
			it->SpawnDefaultController();
			MonsterCount++;
		}
	SpawnCheck = true;

}

// Called every frame
void AObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

