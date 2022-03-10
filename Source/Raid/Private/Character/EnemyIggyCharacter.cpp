// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyIggyCharacter.h"

#include <Raid/Public/Controller/IggyEnemyController.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <Animation/AnimBlueprint.h>

AEnemyIggyCharacter::AEnemyIggyCharacter()
{

	//Super::AEnemyCharacterBase();

	AIControllerClass = AIggyEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMesh(TEXT("SkeletalMesh'/Game/ParagonIggyScorch/Characters/Heroes/IggyScorch/Meshes/IggyScorch.IggyScorch'"));
	if (SkelMesh.Succeeded())
	{
		SkeletaMesh = SkelMesh.Object;
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPObject(TEXT("/Game/ParagonIggyScorch/Characters/Heroes/IggyScorch/IggyScorch_AnimBP"));
	if (AnimBPObject.Succeeded())
	{
		AnimBP = AnimBPObject.Class;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeAttackObject(TEXT("AnimMontage'/Game/Character/Animation/Iggy/IggyMeleeAttack.IggyMeleeAttack'"));
	if (MeleeAttackObject.Succeeded())
	{
		Montage.Add(TEXT("Melee"), MeleeAttackObject.Object);
	}


	GetCapsuleComponent()->InitCapsuleSize(78.0f, 96.0f);

	GetMesh()->SetRelativeLocationAndRotation((FVector(0.0, 0.0, -96.0f)), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetSkeletalMesh(SkeletaMesh);
	GetMesh()->SetAnimInstanceClass(AnimBP->GetClass());

	

}

void AEnemyIggyCharacter::PlayMontage(UAnimMontage* _montage)
{
	Super::PlayMontage(_montage);
}

void AEnemyIggyCharacter::BeginPlay()
{
	Super::BeginPlay();


}

void AEnemyIggyCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void AEnemyIggyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

float AEnemyIggyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float TotalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return TotalDamage;
}
