// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/BladeUltimate.h"
#include <Engine/Classes/Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ABladeUltimate::ABladeUltimate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OneHit = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);
	Damage = 0;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("AttackBox"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetSphereRadius(0.0f);
	/*SphereComponent->OnComponentHit.AddDynamic(this, &ABladeSwipeEffect::Hit);*/

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AttackParticle"));
	Particle->SetupAttachment(SphereComponent);
	Particle->bAutoActivate = true;
	time = 0;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SkillEffectObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Combat_Base/WeaponCombo/Ultimate.Ultimate'"));
	if (SkillEffectObject.Succeeded())
	{
		Particle->SetTemplate(SkillEffectObject.Object);
	}
}

void ABladeUltimate::SetBeginOverlap()
{
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABladeUltimate::OnPlayerEnter);
	SphereComponent->SetSphereRadius(500.0f);
	this->SetActorLocation(GetActorLocation() + 1);
}

void ABladeUltimate::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->ActorHasTag("Enemy"))
	{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HIt"));
		}

		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, NULL, NULL);

	}
}

// Called when the game starts or when spawned
void ABladeUltimate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABladeUltimate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;
	if (time > 0.7f && !OneHit)
	{
		OneHit = true;
		SphereComponent->SetSphereRadius(500.0f);
		
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("HHH"));
	}
	else if (time > 0.3f && time < 0.7f)
	{
		SphereComponent->SetSphereRadius(0.0f);
	}

	this->SetActorLocation(GetActorLocation() + 0.1f);

	if (time > 0.8f)
	{
		SphereComponent->SetSphereRadius(0.0f);
	}
}

