// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyControllerBase.h"
const FName AEnemyControllerBase::HomePosKey(TEXT("HomePosKey"));
const FName AEnemyControllerBase::TargetLocation(TEXT("TargetLocation"));

AEnemyControllerBase::AEnemyControllerBase()
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
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyControllerBase::OnSenseUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AEnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent() != nullptr)
	{
		if (Character != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("All System Set"));
			BBComp->SetValueAsVector(HomePosKey, Character->GetTransform().GetLocation());
			HomeVector = BBComp->GetValueAsVector(HomePosKey);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Some problem"));
	}
}

void AEnemyControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyControllerBase::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);


	if (Character != nullptr)
	{
		HomeDistance = FVector::Distance(Character->GetActorLocation(), HomeVector);




		if (HomeDistance > AISightRadius + 1500.0f)
		{
			BBComp->SetValueAsBool(bb_Keys::enemy_range_over, true);
		}
		else if (HomeDistance < 100.0f)
		{
			BBComp->SetValueAsBool(bb_Keys::enemy_range_over, false);
		}
	}
	//if (DistancePlayer > AISightRadius)
	//{
	//	bIsPlayerDetected = false;
	//}
	//if (Character->GetNextWayPoint() != nullptr && !bIsPlayerDetected)
	//{
	//	MoveToActor(Character->GetNextWayPoint(), 5.0f);
	//}
	//else if (bIsPlayerDetected)
	//{
	//	AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//	DistancePlayer = GetPawn()->GetDistanceTo(Target);
	//	if (DistancePlayer < AIAttackRadius)
	//	{
	//		if (!Character->GetAttack())
	//		{
	//			if (!TimerStop)
	//			{
	//				Distance = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), Player->GetActorLocation());

	//				if (GEngine)
	//				{
	//					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Distance.ToString());
	//				}
	//			}
	//			Direct = FMath::RInterpTo(Character->GetActorRotation(), Distance, DeltaSecond * 10, 1.0f);
	//			StopMovement();
	//			Character->SetActorRotation(Direct);

	//			if (!TimerStop)
	//			{

	//				TimerStop = true;
	//				GetWorldTimerManager().SetTimer(timer, this, &AEnemyControllerBase::MonsterAttack, 0.3f, false, 0.3f);

	//			}
	//		}
	//	}
	//	else
	//	{
	//		MoveToActor(Player, 5.0f);
	//		if (Player != nullptr)
	//		{


	//		}
	//	}
	//}
}

FRotator AEnemyControllerBase::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AEnemyControllerBase::MonsterAttack()
{
	//Character->PlayPattonMontage();
	GetWorldTimerManager().ClearTimer(timer);
	TimerStop = false;
}


void AEnemyControllerBase::OnSenseUpdated(AActor* actor, FAIStimulus const Stimulus)
{

	if (auto const player = Cast<AMyCharacter>(actor))
	{
		//성공적으로 감지하면 블랙보드에 true값을 넣어준다.
		BBComp->SetValueAsBool(bb_Keys::can_see_player, Stimulus.WasSuccessfullySensed());


	}
	bIsPlayerDetected = true;
}