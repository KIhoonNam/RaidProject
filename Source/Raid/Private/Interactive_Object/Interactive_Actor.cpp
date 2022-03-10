// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive_Object/Interactive_Actor.h"

// Sets default values
AInteractive_Actor::AInteractive_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	RootComponent = StaticMesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponents"));

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponents"));


	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/Character/UI/WBP_InteractiveWidget"));
	if (WidgetClassFinder.Succeeded())
	{
		WidgetClass = WidgetClassFinder.Class;
	}

	Widget->SetWidgetClass(WidgetClass);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetDrawSize(FVector2D(32.0f, 32.0f));
	Widget->SetVisibility(false);

	

}

// Called when the game starts or when spawned
void AInteractive_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AInteractive_Actor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor != nullptr && OtherActor->ActorHasTag("Player"))
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Silver, TEXT("HIT"));
//	}
//}
//
//void AInteractive_Actor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor != nullptr && OtherActor->ActorHasTag("Player"))
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Silver, TEXT("Out"));
//	}
//}

// Called every frame
void AInteractive_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractive_Actor::RunInteractive()
{

}

