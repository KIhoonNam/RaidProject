// Fill out your copyright notice in the Description page of Project Settings.

#include <Raid/Public/Controller/GreatSwordAIController.h>
#include <Raid/Public/Etc/WayPoint.h>
#include <Raid/Public/Character/GreatSwordCharacter.h>
#include <Perception/AIPerceptionComponent.h>
#include <Raid/Public/Character/MyCharacter.h>

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

#include <Perception/AISenseConfig_Sight.h>

#include <Kismet/KismetMathLibrary.h>


AGreatSwordAIController::AGreatSwordAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightAge;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AGreatSwordAIController::OnSenseUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	
}

void AGreatSwordAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent() != nullptr)
	{
		Character = Cast<AGreatSwordCharacter>(GetPawn());
		UE_LOG(LogTemp, Warning, TEXT("All System Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Some problem"));
	}
}

void AGreatSwordAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGreatSwordAIController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

	if (DistancePlayer > AISightRadius)
	{
		bIsPlayerDetected = false;
	}
	if (Character->NextWayPoint != nullptr && !bIsPlayerDetected)
	{
		MoveToActor(Character->NextWayPoint, 5.0f);
	}
	else if (bIsPlayerDetected)
	{
		AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		DistancePlayer = GetPawn()->GetDistanceTo(Target);
		if (DistancePlayer  < AIAttackRadius)
		{
			if (!Character->Attack)
			{
				if (!TimerStop)
				{
					Distance = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), Player->GetActorLocation());
					
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Distance.ToString());
					}
				}
				Direct = FMath::RInterpTo(Character->GetActorRotation(), Distance, DeltaSecond * 10, 0.5f);
				StopMovement();
				Character->SetActorRotation(Direct);
			
				if (!TimerStop)
				{
					
					TimerStop = true;
					GetWorldTimerManager().SetTimer(timer, this, &AGreatSwordAIController::MonsterAttack, 0.3f, false,0.3f);
					
				}
			}
		}
		else
		{
			MoveToActor(Player, 5.0f);
			if (Player != nullptr)
			{
			
				
			}
		}
	}

}

FRotator AGreatSwordAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f,0.0f,0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AGreatSwordAIController::MonsterAttack()
{
	Character->PlayPattonMontage();
	GetWorldTimerManager().ClearTimer(timer);
	TimerStop = false;
}

void AGreatSwordAIController::OnSenseUpdated(const TArray<AActor*>& DetectedPawns)
{

	for (size_t i = 0; i < DetectedPawns.Num(); i++)
	{
		DistancePlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
		Target = DetectedPawns[i];
		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), DistancePlayer);
	}
	bIsPlayerDetected = true;
}
