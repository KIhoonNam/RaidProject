// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyRampageCharacter.h"

#include <Raid/Public/Controller/RampageEnemyController.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <Animation/AnimBlueprint.h>

AEnemyRampageCharacter::AEnemyRampageCharacter()
{
	//Super::AEnemyCharacterBase();

	AIControllerClass = ARampageEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMesh(TEXT("SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Skins/Tier2/Elemental/Meshes/Rampage_Elemental.Rampage_Elemental'"));
	if (SkelMesh.Succeeded())
	{
		SkeletaMesh = SkelMesh.Object;
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPObject(TEXT("/Game/ParagonRampage/Characters/Heroes/Rampage/Rampage_AnimBlueprint"));
	if (AnimBPObject.Succeeded())
	{
		AnimBP = AnimBPObject.Class;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeAttackObject(TEXT("AnimMontage'/Game/Character/Animation/Rampage/RampageMeleeAttack.RampageMeleeAttack'"));
	if (MeleeAttackObject.Succeeded())
	{
		Montage.Add(TEXT("Melee"),MeleeAttackObject.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PattonOneObject(TEXT("AnimMontage'/Game/Character/Animation/Rampage/RampagePattonOne.RampagePattonOne'"));
	if (PattonOneObject.Succeeded())
	{
		Montage.Add(TEXT("PattonOne"), PattonOneObject.Object);
	}

	GetCapsuleComponent()->InitCapsuleSize(78.0f, 96.0f);

	GetMesh()->SetRelativeLocationAndRotation((FVector(0.0, 0.0, -96.0f)),FRotator(0.0f,-90.0f,0.0f));
	GetMesh()->SetSkeletalMesh(SkeletaMesh);
	GetMesh()->SetAnimInstanceClass(AnimBP->GetClass());
	
}

void AEnemyRampageCharacter::PlayMontage(UAnimMontage* _montage)
{
	Super::PlayMontage(_montage);

	
}

void AEnemyRampageCharacter::BeginPlay()
{
	Super::BeginPlay();


}

void AEnemyRampageCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AEnemyRampageCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

float AEnemyRampageCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float TotalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return TotalDamage;
}

