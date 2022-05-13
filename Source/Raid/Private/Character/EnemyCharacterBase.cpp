// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacterBase.h"
#include <Raid/Public/Controller/EnemyControllerBase.h>

// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Hp = 5000;
	Damage = 20000;
	Armor = 1000;
	Name = TEXT("Velganus");

	EnemyType = EEnemyType::IDLE;

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

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageObject(TEXT("AnimMontage'/Game/Character/Animation/GreatSword_Attack10_Montage.GreatSword_Attack10_Montage'"));
	//if (AttackMontageObject.Succeeded())
	//	AttackMontage = AttackMontageObject.Object;

	//static ConstructorHelpers::FObjectFinder<UBlueprint> PattonOnewEffectObject(TEXT("Blueprint'/Game/Character/Effect/GreatBurstEffect_BP.GreatBurstEffect_BP'"));
	//if (PattonOnewEffectObject.Object)
	//{
	//	PattonOneEffect = (UClass*)PattonOnewEffectObject.Object->GeneratedClass;
	//}


}

void AEnemyCharacterBase::PlayMontage(UAnimMontage* _montage)
{
	PlayAnimMontage(_montage);

}

// Called when the game starts or when spawned
void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpawnDefaultController();
}

void AEnemyCharacterBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AEnemyCharacterBase::FadeOutTimer()
{
	float ParameterValue;
		for (int i = 0; i < DynamicMaterial.Num(); i++)
		{
			
			DynamicMaterial[i]->GetScalarParameterValue(TEXT("FadeOut"), ParameterValue);
			float Sum = ParameterValue - 0.05f;
			DynamicMaterial[i]->SetScalarParameterValue(TEXT("FadeOut"), Sum);
	
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Set"));
		if (ParameterValue <= 0.0f)
		{
			AEnemyControllerBase* EnemyController = Cast<AEnemyControllerBase>(this->GetController());
			EnemyController->GetBlackboardComponent()->SetValueAsBool(bb_Keys::start, true);
			GetWorld()->GetTimerManager().ClearTimer(FadeHandle);
		}
	

		
	
	
}

float AEnemyCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float TotalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (TotalDamage >= 0)
	{

		AEnemyControllerBase* EnemyController = Cast<AEnemyControllerBase>(this->GetController());
		EnemyController->GetBlackboardComponent()->SetValueAsBool(bb_Keys::hit_check, true);

		DamageWidget = CreateWidget<UDamageText>(GetWorld(), DamageWidgetClass);

		if (DamageWidget)
		{
			DamageWidget->SetPosition(FVector2D(FMath::RandRange(-15.0f, 15.0f)));
			DamageWidget->GetActor(this);
			DamageWidget->SetDamage(TotalDamage);
			DamageWidget->AddToViewport();

		}
	}

	
	return TotalDamage;
}

// Called every frame
void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void AEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

