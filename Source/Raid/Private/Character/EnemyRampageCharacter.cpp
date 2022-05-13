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
		Montage.Add(TEXT("Melee"), MeleeAttackObject.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitObject(TEXT("AnimMontage'/Game/Character/Animation/Rampage/RampageHit.RampageHit'"));
	if (MeleeAttackObject.Succeeded())
	{
		Montage.Add(TEXT("Hit"), HitObject.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathObject(TEXT("AnimMontage'/Game/Character/Animation/Rampage/RampageDeath.RampageDeath'"));
	if (MeleeAttackObject.Succeeded())
	{
		Montage.Add(TEXT("Death"), DeathObject.Object);
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


	float waitTime= 0.1f;
	GetWorld()->GetTimerManager().SetTimer(FadeHandle,this, &AEnemyRampageCharacter::FadeOutTimer, waitTime, true);

}

void AEnemyRampageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


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

