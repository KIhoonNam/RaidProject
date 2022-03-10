// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Effect/GreatBurstEffect.h>
#include <Engine/Classes/Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>
#include <UObject/ConstructorHelpers.h>
#include <Raid/Public/Etc/CharacterDamageType.h>
#include <Raid/Public/Character/GreatSwordCharacter.h>

// Sets default values
AGreatBurstEffect::AGreatBurstEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChDamageType = UCharacterDamageType::StaticClass();
	
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("AttackBox"));
	SphereComponent->SetupAttachment(GetRootComponent());

	SphereComponent->SetSphereRadius(0.0f);
	SphereComponent->SetGenerateOverlapEvents(false);
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AttackParticle"));
	Particle->SetupAttachment(SphereComponent);
	Particle->bAutoActivate = true;
}

// Called when the game starts or when spawned
void AGreatBurstEffect::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AGreatBurstEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time += DeltaTime;

	if(time >= 0.25f)
	SphereComponent->SetGenerateOverlapEvents(false);
}

void AGreatBurstEffect::SetDamage(float damage)
{
	Damage = damage;
}

void AGreatBurstEffect::SetBeginOverlap(AActor* actor)
{
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGreatBurstEffect::OnPlayerEnter);
	SphereComponent->SetSphereRadius(150.0f);
	SphereComponent->SetGenerateOverlapEvents(true);
	Character = actor;
	this->SetActorLocation(GetActorLocation() + 1);
}

void AGreatBurstEffect::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor != GetOwner() && OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, Character, ChDamageType);
	}
}

