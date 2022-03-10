// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BladeCharacter.h"

ABladeCharacter::ABladeCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageObject(TEXT("AnimMontage'/Game/Character/Animation/TwinBlade_MeleeAttack.TwinBlade_MeleeAttack'"));
	if (AttackMontageObject.Succeeded())
		AttackMontage = AttackMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DashMontageObject(TEXT("AnimMontage'/Game/Character/Animation/TwinBlade_Dash.TwinBlade_Dash'"));
	if (DashMontageObject.Succeeded())
		DashMontage = DashMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DashAttackMontageObject(TEXT("AnimMontage'/Game/Character/Animation/TwinBlade_DashAttack.TwinBlade_DashAttack'"));
	if (DashAttackMontageObject.Succeeded())
		DashAttackMontage = DashAttackMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FalldownMontageObject(TEXT("AnimMontage'/Game/Character/Animation/TwinBlade_Falldown.TwinBlade_Falldown'"));
	if (FalldownMontageObject.Succeeded())
		FalldownMontage = FalldownMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DodgeMontageObject(TEXT("AnimMontage'/Game/Character/Animation/TwinBlade_StUp.TwinBlade_StUp'"));
	if (DodgeMontageObject.Succeeded())
		DodgeMontage = DodgeMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> UltimateMontageObject(TEXT("AnimMontage'/Game/Character/Animation/TwinBlade_Ultimate.TwinBlade_Ultimate'"));
	if (UltimateMontageObject.Succeeded())
		UltimateMontage = UltimateMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UBlueprint> QSkillEffectColObject(TEXT("Blueprint'/Game/Character/Effect/BladeSwipeEffectCol.BladeSwipeEffectCol'"));
	if (QSkillEffectColObject.Object)
	{
		QSkillEffectCol = (UClass*)QSkillEffectColObject.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> UltimateSkillObject(TEXT("Blueprint'/Game/Character/Effect/BPE_BladeUltimate.BPE_BladeUltimate'"));
	if (UltimateSkillObject.Object)
	{
		UltimateEffect = (UClass*)UltimateSkillObject.Object->GeneratedClass;
	}

	static ConstructorHelpers::FClassFinder<UDamageText> DamageTextClass(TEXT("/Game/Character/UI/WBP_DamageText"));
	if (DamageTextClass.Succeeded())
	{
		DamageWidgetClass = DamageTextClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UGameUI> GameUIWidgetClasss(TEXT("/Game/Character/UI/WBP_GameUI"));
	if (GameUIWidgetClasss.Succeeded())
	{
		GameUIWidgetClass = GameUIWidgetClasss.Class;
	}

	static ConstructorHelpers::FClassFinder<USlotWidget> InventoryWidgetClass(TEXT("/Game/Character/UI/WBP_SlotWidget"));
	if (GameUIWidgetClasss.Succeeded())
	{
		InvenClass = InventoryWidgetClass.Class;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableObject(TEXT("DataTable'/Game/Character/Animation/SkillData.SkillData'"));
	if (DataTableObject.Succeeded())
	{
		SkillDataTable = DataTableObject.Object;
	}

	
}

ABladeCharacter::~ABladeCharacter()
{
}

void ABladeCharacter::SetSkill()
{

	


	PlayerSkill.Init(FSkillData1::FSkillData1(), 8);
	if (SkillDataTable != NULL)
	{
		PlayerSkill[0] = *SkillDataTable->FindRow<FSkillData1>("DashAttack", TEXT("HI"));
		PlayerSkill[1] = *SkillDataTable->FindRow<FSkillData1>("Dash", TEXT("HI"));
		PlayerSkill[2] = *SkillDataTable->FindRow<FSkillData1>("Dodge", TEXT("HI"));
		PlayerSkill[3] = *SkillDataTable->FindRow<FSkillData1>("Ulti", TEXT("HI"));
	}
}

float ABladeCharacter::GetDashCool()
{
	return DashCool;
}

void ABladeCharacter::DashAnimMontagePlay()
{
	Super::DashAnimMontagePlay();
}

void ABladeCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	

	

	Hp = 60000;
	FullHp = 60000;
	Mp = 3091;
	FullMp = 3091;
	Damage = 19000;
	Armor = 20000;
	Name = TEXT("³¢¾ßÁH");
	Exp = 0;


}

void ABladeCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(Hp));

	SetSkill();
	if (GameUIWidgetClass)
	{
		GameUIWidget = CreateWidget<UGameUI>(GetWorld(), GameUIWidgetClass);
		GameUIWidget->SetPlayer(this);
		GameUIWidget->AddToViewport();
	}
}


