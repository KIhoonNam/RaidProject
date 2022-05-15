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
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitObject(TEXT("AnimMontage'/Game/Character/Animation/Iggy/IggyHit.IggyHit'"));
	if (MeleeAttackObject.Succeeded())
	{
		Montage.Add(TEXT("Hit"), HitObject.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathObject(TEXT("AnimMontage'/Game/Character/Animation/Iggy/IggyDeath.IggyDeath'"));
	if (MeleeAttackObject.Succeeded())
	{
		Montage.Add(TEXT("Death"), DeathObject.Object);
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
	Material.Init(nullptr, GetMesh()->GetNumMaterials());

	for (int i = 0; i < Material.Num(); i++)
	{

		Material[i] = GetMesh()->GetMaterial(i);
	}

	DynamicMaterial.Init(nullptr, Material.Num());

	for (int i = 0; i < DynamicMaterial.Num(); i++)
	{

		DynamicMaterial[i] = UMaterialInstanceDynamic::Create(Material[i], this);
	}

	for (int i = 0; i < GetMesh()->GetNumMaterials(); i++)
	{

		GetMesh()->SetMaterial(i, DynamicMaterial[i]);
	}

	for (int i = 0; i < DynamicMaterial.Num(); i++)
	{

		DynamicMaterial[i]->SetScalarParameterValue(TEXT("FadeOut"), 1.0f);
	}


	float waitTime = 0.1f;
	GetWorld()->GetTimerManager().SetTimer(FadeHandle, this, &AEnemyIggyCharacter::FadeOutTimer, waitTime, true);

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
