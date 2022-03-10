// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Etc/WayPoint.h>
#include <Raid/Public/Character/GreatSwordCharacter.h>
// Sets default values
AWayPoint::AWayPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	BoxComponet = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Compnenet"));
	BoxComponet->SetupAttachment(GetRootComponent());
	BoxComponet->OnComponentBeginOverlap.AddDynamic(this, &AWayPoint::OnPlayerEnter);
	BoxComponet->InitBoxExtent(FVector(80.0f, 80.0f, 90.0f));
}

// Called when the game starts or when spawned
void AWayPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWayPoint::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGreatSwordCharacter* Character = nullptr;
	if (OtherActor != nullptr)
	{
		Character = Cast<AGreatSwordCharacter>(OtherActor);
		if (Character != nullptr)
		{
			Character->NextWayPoint = NextWayPoint;
		}
	}
}

