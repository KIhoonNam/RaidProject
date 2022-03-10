// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Character/GreatSwordCharacter.h>
#include <Raid/Public/Etc/WayPoint.h>
#include <Raid/Public/Effect/GreatBurstEffect.h>
#include <Components/WidgetComponent.h>
#include <Blueprint/UserWidget.h>
#include <Raid/Public/UI/DamageText.h>
#include <Kismet/GameplayStatics.h>
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"

// Sets default values
AGreatSwordCharacter::AGreatSwordCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Hp = 5000;
	Damage = 20000;
	Armor = 1000;
	Name = TEXT("Velganus");

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	static ConstructorHelpers::FClassFinder<UDamageText> DamageTextClass(TEXT("/Game/Character/UI/WBP_DamageText"));
	if (DamageTextClass.Succeeded())
	{
		DamageWidgetClass = DamageTextClass.Class;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageObject(TEXT("AnimMontage'/Game/Character/Animation/GreatSword_Attack10_Montage.GreatSword_Attack10_Montage'"));
	if (AttackMontageObject.Succeeded())
		AttackMontage = AttackMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UBlueprint> PattonOnewEffectObject(TEXT("Blueprint'/Game/Character/Effect/GreatBurstEffect_BP.GreatBurstEffect_BP'"));
	if (PattonOnewEffectObject.Object)
	{
		PattonOneEffect = (UClass*)PattonOnewEffectObject.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AGreatSwordCharacter::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void AGreatSwordCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreatSwordCharacter::PlayPattonMontage()
{
	if (!Attack)
	{
		FTimerHandle Timer;
		Attack = true;
		PlayAnimMontage(AttackMontage, 1.0f);
		GetWorld()->GetTimerManager().SetTimer(Timer,this,&AGreatSwordCharacter::PattonOne,0.7f,false);
	}
}

void AGreatSwordCharacter::PattonOne()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UE_LOG(LogTemp, Log, TEXT("SpawnAmmo"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		FRotator rotator;
		FVector  SpawnLocation = GetActorLocation() + GetActorForwardVector() * 200;


		class AGreatBurstEffect* PattonOneSkill = world->SpawnActor<AGreatBurstEffect>(PattonOneEffect, SpawnLocation, rotator, SpawnParams);
		if (PattonOneSkill)
		{
			PattonOneSkill->SetActorLocation(SpawnLocation);
			PattonOneSkill->SetDamage(2000);
			PattonOneSkill->SetBeginOverlap(this);
			

		}
	}
}

float AGreatSwordCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float TotalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (TotalDamage >= 0)
	{
		DamageWidget = CreateWidget<UDamageText>(GetWorld(), DamageWidgetClass);

		if (DamageWidget)
		{
			DamageWidget->SetPosition(FVector2D(FMath::RandRange(-15.0f, 15.0f)));
			DamageWidget->GetActor(this);
			DamageWidget->SetDamage(TotalDamage);
			DamageWidget->AddToViewport();
		
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("HI"));

	return TotalDamage;
}

// Called to bind functionality to input
void AGreatSwordCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

