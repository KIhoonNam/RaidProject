// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Character/MyCharacter.h>

#include <GameFramework/Actor.h>

#include "Engine/Classes/Components/CapsuleComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"





// Sets default values
AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;




	



	Attackindex = 1;
	bAttackable = false;
	CSTATE = ECharacterState::IDLE;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello"));

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	AttackBox1 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackBox1"));
	AttackBox1->SetupAttachment(this->GetMesh());
	AttackBox1->InitCapsuleSize(8.4f, 70.0f);
	AttackBox1->SetRelativeLocationAndRotation(FVector(0, 0, 0.0f), FRotator(FRotator(0, 0.0f, 0.0f)));
	AttackBox1->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ik_hand_r"));

	AttackBox1->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMyCharacter::OnHit);
	

	AttackBox1->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	RpgCameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("RpgCameraSpringArm"));
	RpgCameraSpringArmComponent->SetupAttachment(RootComponent);
	RpgCameraSpringArmComponent->SetUsingAbsoluteRotation(true);
	RpgCameraSpringArmComponent->TargetArmLength = 1200.0f;
	RpgCameraSpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	RpgCameraSpringArmComponent->bDoCollisionTest = false;

	RpgCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RpgCamera"));
	RpgCameraComponent->SetupAttachment(RpgCameraSpringArmComponent, USpringArmComponent::SocketName);
	RpgCameraComponent->bUsePawnControlRotation = false;


}



void AMyCharacter::AnimMontagePlay()
{

	
	FString Attackname = FString::FromInt(Attackindex) + TEXT("_Start");
	FName Attacks = FName(*Attackname);
	PlayAnimMontage(AttackMontage, 1.0f, Attacks);

	FString  name = AttackMontage->GetName();
	//
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(Attackindex)  + "");
	//}
}

void AMyCharacter::DashAnimMontagePlay()
{
	PlayAnimMontage(DashMontage, 1.0f);

	DashCool = 10;
	Infinity = true;
}

void AMyCharacter::QSkillAnimMontagePlay()
{
	FSkillData1* Skill = SkillDataTable->FindRow<FSkillData1>(PlayerSkill[0].Name,TEXT("Hi"));
	if (Skill)
	{
		if (QSkillCool <= 0)
			QSkillCool = Skill->Cool;
		PlayAnimMontage(Skill->AnimMontage);

		SkillEffect(Skill);
	}	
}

void AMyCharacter::FalldownAnimMontagePlay()
{
	PlayAnimMontage(FalldownMontage, 1.0f);
	
	

	CSTATE = ECharacterState::ABNORMAL;

}

void AMyCharacter::DodgeAnimMontagePlay()
{
	PlayAnimMontage(DodgeMontage, 1.0f);

	DodgeCool = 10;

	Infinity = true;
}

void AMyCharacter::UltimateAnimMontagePlay()
{
	PlayAnimMontage(UltimateMontage, 1.0f);

	UltiCool = 300;

	FTimerHandle UltiTime;
	GetWorld()->GetTimerManager().SetTimer(UltiTime, this, &AMyCharacter::UltimateAttack, 0.84f, false);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();



	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AMyCharacter::MpRegen, 1.0f, true, 1.0f);

}
void AMyCharacter::MpRegen()
{
	
	Mp += FullMp * 0.07f;
	if (Mp > FullMp)
		Mp = FullMp;
}

float AMyCharacter::GetQCool()
{
	return QSkillCool;
}
float AMyCharacter::GetDodgeCool()
{
	return DodgeCool;
}
float AMyCharacter::GetDashCool()
{
	return DashCool;
}
float AMyCharacter::GetUltiCool()
{
	return UltiCool;
}
float AMyCharacter::GetMaxHp()
{
	return FullHp;
}
float AMyCharacter::GetCurrentHp()
{
	return Hp;
}
float AMyCharacter::GetMaxMp()
{
	return FullMp;
}
float AMyCharacter::GetCurrentMp()
{
	return Mp;
}
void AMyCharacter::AttackAble(bool enable)
{
	bAttackable = enable;
}
void AMyCharacter::ForwardMove(float deltaTime,float speed)
{
	



	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * speed;
	LaunchCharacter(GetActorForwardVector() * speed, false, false);

	
}
void AMyCharacter::SetAttackIndex(int32 index)
{
	Attackindex += index;
}
void AMyCharacter::SetInfinity(bool enable)
{
	Infinity = enable;
}
int32 AMyCharacter::GetAttackIndex()
{
	return Attackindex;
}
bool AMyCharacter::GetAttackable()
{
	return bAttackable;
}

void AMyCharacter::SwapSkill(int from, int to)
{
	FSkillData1 skill = PlayerSkill[from];
	PlayerSkill[from] = PlayerSkill[to];
	PlayerSkill[to] = skill;
	GameUIWidget->UpdateSkill();
}

ECharacterState AMyCharacter::GetState()
{
	return CSTATE;
}

FSkillData1 AMyCharacter::GetSkillData(int num)
{
	return PlayerSkill[num];
}

void AMyCharacter::SetState(ECharacterState state)
{
	CSTATE = state;
}

void AMyCharacter::IdleState()
{
	

}

void AMyCharacter::SkillEffect(FSkillData1* _skill)
{
	UWorld* world = GetWorld();
	if (world)
	{
		UE_LOG(LogTemp, Log, TEXT("SpawnAmmo"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		FRotator rotator;
		FVector  SpawnLocation = GetActorLocation();

		if (_skill->Name == "DashAttack")
		{
			class ABladeSwipeEffect* Skill = world->SpawnActor<ABladeSwipeEffect>(QSkillEffectCol, SpawnLocation, rotator, SpawnParams);
			if (Skill)
			{
				Skill->Damage = _skill->Damage;
				Skill->SetBeginOverlap();
				Mp -= _skill->Mana;
			}
		}
		else if (_skill->Name == "Ulti")
		{
			class ABladeUltimate* Skill = world->SpawnActor<ABladeUltimate>(UltimateEffect, SpawnLocation, rotator, SpawnParams);
			if (Skill)
			{
				Skill->Damage = _skill->Damage;
				Skill->SetBeginOverlap();
				Mp -= _skill->Mana;
			} 
		}


	}

}


void AMyCharacter::InputAttackPressed()
{
	bClickAttack = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("TEXT"));
	}

}

void AMyCharacter::InputAttackReleased()
{
	bClickAttack = false;
}

void AMyCharacter::UltimateAttack()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UE_LOG(LogTemp, Log, TEXT("SpawnAmmo"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		FRotator rotator;
		FVector  SpawnLocation = GetActorLocation();


		class ABladeUltimate* UltimateSkill = world->SpawnActor<ABladeUltimate>(UltimateEffect, SpawnLocation, rotator, SpawnParams);
		if (UltimateSkill)
		{
			UltimateSkill->Damage = 2000;
			UltimateSkill->SetBeginOverlap();
			Mp -= 204;
		}
	}
}



void AMyCharacter::SetStop(bool _stop)
{
	Stop = _stop;
}

void AMyCharacter::SetAttackBox(bool enable)
{
	AttackBox1->SetGenerateOverlapEvents(enable);
}



// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Position;
	if (bClickAttack)
	{
		AnimMontagePlay();


	}
	if (GEngine)
	{
		
	}
	DashCool -= DeltaTime;
	QSkillCool -= DeltaTime;
	DodgeCool -= DeltaTime;
	UltiCool -= DeltaTime;
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//InputComponent->BindAction("Attack", IE_Pressed, this, &AMyCharacter::InputAttackPressed);
	//InputComponent->BindAction("Attack", IE_Released, this, &AMyCharacter::InputAttackReleased);
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float TotalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UDamageType* DamageType = Cast<UDamageType>(DamageEvent.DamageTypeClass.GetDefaultObject());

	if (DamageType->IsA(UCharacterDamageType::StaticClass()) && !Infinity)
	{
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),DamageCauser->GetActorLocation()));
		FalldownAnimMontagePlay();
		Controller->StopMovement();
	}
	if (TotalDamage >= 0)
	{
		Hp -= TotalDamage;
		DamageWidget = CreateWidget<UDamageText>(GetWorld(), DamageWidgetClass);

		if (DamageWidget)
		{
			DamageWidget->SetPosition(FVector2D(FMath::RandRange(-15.0f, 15.0f)));
			DamageWidget->GetActor(this);
			DamageWidget->SetDamage(TotalDamage);
			DamageWidget->AddToViewport();

		}
	}

	return 0.0f;
}

void AMyCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, OtherActor->GetName());
	}
}

void AMyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_GameTraceChannel2 && CSTATE == ECharacterState::ATTACK)
	{
		GetMovementComponent()->StopMovementImmediately();
	}

}

void AMyCharacter::SetSkill()
{
	UE_LOG(LogWindows, Warning, TEXT("SetSkillFunction"));
}




