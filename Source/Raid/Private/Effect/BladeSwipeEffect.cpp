// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Effect/BladeSwipeEffect.h>
#include <Engine/Classes/Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Raid/Public/Character/MyCharacter.h>


// Sets default values
ABladeSwipeEffect::ABladeSwipeEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

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

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SkillEffectObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Melee/P_Spin_Blades.P_Spin_Blades'"));
	if (SkillEffectObject.Succeeded())
	{
		Particle->SetTemplate(SkillEffectObject.Object);
	}
}

// Called when the game starts or when spawned
void ABladeSwipeEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABladeSwipeEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetActorLocation(Player->GetActorLocation());
	time += DeltaTime;

	if (time >= 0.18f)
	{
		SphereComponent->SetSphereRadius(230.0f);
	
	}

}

void ABladeSwipeEffect::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (Other != this && Other != GetOwner())
	//{
	//		if (GEngine)
	//		{
	//			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("HIt"));
	//		}
	//	UGameplayStatics::ApplyDamage(Other, Damage, NULL, Player, NULL);
	//}
}

void ABladeSwipeEffect::SetBeginOverlap()
{
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABladeSwipeEffect::OnPlayerEnter);
	SphereComponent->SetSphereRadius(230.0f);
}



//void ABladeSwipeEffect::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	if (OtherActor != this && OtherActor != GetOwner())
//	{
//		/*	if (GEngine)
//			{
//				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("HIt"));
//			}*/
//		
//	}
//}

void ABladeSwipeEffect::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor != this && OtherActor->ActorHasTag("Enemy"))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HIt"));
		}
		
		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, Player, NULL);
		SphereComponent->SetSphereRadius(0.0f);
		time = 0;
	}

}

