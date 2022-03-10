// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/IggyEnemyController.h"

#include <Raid/Public/Character/EnemyIggyCharacter.h>

AIggyEnemyController::AIggyEnemyController()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Character/BehaviorTree/RampageBlackBoard.RampageBlackBoard'"));
	if (BBObject.Succeeded())
	{

		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Character/BehaviorTree/IggyBehaviorTree.IggyBehaviorTree'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponents"));

}

void AIggyEnemyController::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AEnemyIggyCharacter>(GetPawn());

	RunBehaviorTree(BTAsset);
	BTComp->StartTree(*BTAsset);
}

void AIggyEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BBComp)
	{
		BBComp->InitializeBlackboard(*BBAsset);
	}
}

void AIggyEnemyController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

FRotator AIggyEnemyController::GetControlRotation() const
{
	Super::GetControlRotation();

	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AIggyEnemyController::OnSenseUpdated(AActor* actor, FAIStimulus const Stimulus)
{
	Super::OnSenseUpdated(actor, Stimulus);
}
