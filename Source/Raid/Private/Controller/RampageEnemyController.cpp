// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/RampageEnemyController.h"

#include <Raid/Public/Character/EnemyRampageCharacter.h>

ARampageEnemyController::ARampageEnemyController()
{


	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Character/BehaviorTree/RampageBlackBoard.RampageBlackBoard'"));
	if (BBObject.Succeeded())
	{
		
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Character/BehaviorTree/RampageBehaviorTree.RampageBehaviorTree'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponents"));
}

void ARampageEnemyController::BeginPlay()
{
	Super::BeginPlay();

		Character = Cast<AEnemyRampageCharacter>(GetPawn());

	RunBehaviorTree(BTAsset);
	BTComp->StartTree(*BTAsset);

	
}

void ARampageEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BBComp)
	{
		BBComp->InitializeBlackboard(*BBAsset);
	}
}

void ARampageEnemyController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

FRotator ARampageEnemyController::GetControlRotation() const
{
	Super::GetControlRotation();

	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void ARampageEnemyController::OnSenseUpdated(AActor* actor, FAIStimulus const Stimulus)
{

	Super::OnSenseUpdated(actor, Stimulus);
}
