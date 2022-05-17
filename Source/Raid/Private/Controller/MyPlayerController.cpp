// Fill out your copyright notice in the Description page of Project Settings.


#include <Raid/Public/Controller/MyPlayerController.h>
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/Character/BladeCharacter.h>
#include <Raid/Public/UI/GameUI.h>


AMyPlayerController::AMyPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;

   
 
}





void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    m_Character = Cast<ABladeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
 
}

void AMyPlayerController::InputClickPressed()
{
   
	bClickMouse = true;
  
}

void AMyPlayerController::InputClikReleased()
{
	bClickMouse = false;
}

void AMyPlayerController::InputAttackPressed()
{
    bClickAttack = true;
    
}

void AMyPlayerController::InputAttackReleased()
{
    bClickAttack = false;
}

void AMyPlayerController::InputDashPressed()
{
    if (m_Character->GetDashCool() <= 0 && m_Character->GetState() == ECharacterState::IDLE)
    {
        bClickDash = true;
        Dash();
    }
    else if (m_Character->GetDodgeCool() <= 0 && m_Character->GetState() == ECharacterState::ABNORMAL)
    {
        if (m_Character->GetVelocity() == FVector(0.0f,0.0f,0.0f))
        {
            bClickDodge = true;
            Dodge();
        }
    }
}

void AMyPlayerController::InputDashReleased()
{
   /* bClickDash =  false;*/
}

void AMyPlayerController::InputQPressed()
{  
      bClickQ = true;
}

void AMyPlayerController::InputQReleased()
{
    bClickQ = false;
}

void AMyPlayerController::InputUltimateReleased()
{
    bClickUltimate = false;
}

void AMyPlayerController::InputUltimatePressed()
{
    bClickUltimate = true;
}

void AMyPlayerController::InputInventoryPressed()
{
    m_Character->GetUI()->SetUIVisible(EUIVisible::Inventory);
}

void AMyPlayerController::InputInventoryReleased()
{

}

void AMyPlayerController::InputSkillPressed()
{
    m_Character->GetUI()->SetUIVisible(EUIVisible::Skill);
}

void AMyPlayerController::InputSkillReleased()
{
}

void AMyPlayerController::InputEquipmentPressed()
{
    m_Character->GetUI()->SetUIVisible(EUIVisible::Equipment);
}

void AMyPlayerController::InputEquipmentReleased()
{
}

void AMyPlayerController::InputInteractivePressed()
{
    if(m_Character->GetInteractiveActor() != NULL)
    m_Character->GetInteractiveActor()->RunInteractive();
}

void AMyPlayerController::InputInteractiveReleased()
{
}

bool AMyPlayerController::GetClickAttack()
{
    return bClickAttack;
}

bool AMyPlayerController::GetDashAttack()
{
    return bClickQ;
}

bool AMyPlayerController::GetDashOne()
{
    return DashOne;
}

void AMyPlayerController::SetAction(bool Enable)
{
    bAction = Enable;
}

void AMyPlayerController::SetClickDash(bool Enable)
{
    bClickDash = Enable;
    DashOne = Enable;
}


void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("Move", IE_Pressed, this, &AMyPlayerController::InputClickPressed);
    InputComponent->BindAction("Move", IE_Repeat, this, &AMyPlayerController::InputClickPressed);
    InputComponent->BindAction("Move", IE_Released, this, &AMyPlayerController::InputClikReleased);

    InputComponent->BindAction("Attack", IE_Pressed, this, &AMyPlayerController::InputAttackPressed);
    InputComponent->BindAction("Attack", IE_Released, this, &AMyPlayerController::InputAttackReleased);

    InputComponent->BindAction("Dash", IE_Pressed, this, &AMyPlayerController::InputDashPressed);
    InputComponent->BindAction("Dash", IE_Released, this, &AMyPlayerController::InputDashReleased);

    InputComponent->BindAction("Q", IE_Pressed, this, &AMyPlayerController::InputQPressed);
    InputComponent->BindAction("Q", IE_Released, this, &AMyPlayerController::InputQReleased);

    InputComponent->BindAction("Ultimate", IE_Pressed, this, &AMyPlayerController::InputUltimatePressed);
    InputComponent->BindAction("Ultimate", IE_Released, this, &AMyPlayerController::InputUltimateReleased);

    InputComponent->BindAction("Inven", IE_Pressed, this, &AMyPlayerController::InputInventoryPressed);
    InputComponent->BindAction("Inven", IE_Released, this, &AMyPlayerController::InputInventoryReleased);

    InputComponent->BindAction("Equipment", IE_Pressed, this, &AMyPlayerController::InputEquipmentPressed);
    InputComponent->BindAction("Equipment", IE_Released, this, &AMyPlayerController::InputEquipmentReleased);

    InputComponent->BindAction("Skill", IE_Pressed, this, &AMyPlayerController::InputSkillPressed);
    InputComponent->BindAction("Skill", IE_Released, this, &AMyPlayerController::InputSkillReleased);

    InputComponent->BindAction("Interactive", IE_Pressed, this, &AMyPlayerController::InputInteractivePressed);
    InputComponent->BindAction("Interactive", IE_Released, this, &AMyPlayerController::InputInteractiveReleased);
}

void AMyPlayerController::SetNewDestination(const FVector destination)
{
    APawn* const MyPawn = GetPawn();
    if (MyPawn)
    {
        float const Distance = FVector::Dist(destination, MyPawn->GetActorLocation());
        m_Character->StopAnimMontage();
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, destination);
    }
}
void AMyPlayerController::MoveToMouseCursor()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_GameTraceChannel5, false, Hit);
    if (Hit.bBlockingHit)
    {        
        //SetNewDestination(Hit.ImpactPoint);
        APawn* const MyPawn = GetPawn();
        if (MyPawn)
        {
            float const Distance = FVector::Dist(Hit.ImpactPoint, MyPawn->GetActorLocation());
          //  m_Character->StopAnimMontage();
    
            AAIController* Control = Cast<AAIController>(m_Character->GetController());
            if (Control != NULL)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("SUCCESE"));
                Control->MoveToLocation(Hit.ImpactPoint, 1.0f);
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("Fail"));
                UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.ImpactPoint);
            }


        }
    }
}
void AMyPlayerController::QSkill()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        APawn* MyPawn = GetPawn();
        if (MyPawn)
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetActorLocation());
            MyPawn->SetActorRotation(FRotator(MyPawn->GetActorRotation().Roll, UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.Location).Yaw, MyPawn->GetActorRotation().Pitch));
            bClickDash = true;
            m_Character->SetState(ECharacterState::ATTACK);
            if (m_Character != NULL)
                m_Character->QSkillAnimMontagePlay();
        }
    }
}
void AMyPlayerController::AttackRotation()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);


    if (Hit.bBlockingHit)
    {

        APawn*  MyPawn = GetPawn();
        if (MyPawn)
        {
           time = 0;
           
           if (!m_Character->GetAttackable())
           {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetActorLocation()); 
            MyPawn->SetActorRotation(FRotator(MyPawn->GetActorRotation().Roll, UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.Location).Yaw, MyPawn->GetActorRotation().Pitch));
            m_Character->AttackAble(true);
            m_Character->SetState(ECharacterState::ATTACK);
                if (m_Character != NULL)
                    m_Character->AnimMontagePlay();
            }
           
        }
    }

}

void AMyPlayerController::Dash()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        APawn* MyPawn = GetPawn();
        if (MyPawn)
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetActorLocation());
            MyPawn->SetActorRotation(FRotator(MyPawn->GetActorRotation().Roll, UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.Location).Yaw, MyPawn->GetActorRotation().Pitch));
            DashOne = true;
            m_Character->SetState(ECharacterState::ATTACK);
            if (m_Character != NULL)
                m_Character->DashAnimMontagePlay();
        }
    }
}

void AMyPlayerController::Dodge()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        APawn* MyPawn = GetPawn();
        if (MyPawn)
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetActorLocation());
            MyPawn->SetActorRotation(FRotator(MyPawn->GetActorRotation().Roll, UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.Location).Yaw, MyPawn->GetActorRotation().Pitch));
            DashOne = true;
            if (m_Character != NULL)
                m_Character->DodgeAnimMontagePlay();
        }
    }
}

void AMyPlayerController::Ultimate()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        APawn* MyPawn = GetPawn();
        if (MyPawn)
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetActorLocation());
            MyPawn->SetActorRotation(FRotator(MyPawn->GetActorRotation().Roll, UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.Location).Yaw, MyPawn->GetActorRotation().Pitch));
            m_Character->SetInfinity(true);
            m_Character->SetState(ECharacterState::ATTACK);
            if (m_Character != NULL)
                m_Character->UltimateAnimMontagePlay();
        }
    }
}



void AMyPlayerController::SetMeleeRotation(AMyCharacter* pawn, FHitResult hit)
{
    pawn->SetActorRotation(FRotator(pawn->GetActorRotation().Roll, UKismetMathLibrary::FindLookAtRotation(pawn->GetActorLocation(), hit.Location).Yaw, pawn->GetActorRotation().Pitch));
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
    

    if (m_Character->GetState() == ECharacterState::IDLE && !UIEnable)
    {
        if (bClickMouse && !m_Character->GetAttackable())
        {
            MoveToMouseCursor();
        }

        if (bClickAttack)
        {
            AttackRotation();
        }

        if (bClickQ && m_Character->GetQCool() <= 0)
        {
            QSkill();
        }

        if (bClickUltimate && m_Character->GetUltiCool() <= 0)
        {
            Ultimate();
        }
    }
    
 /*   UE_LOG(LogTemp, Warning, TEXT("%s"), bClickDash ? TEXT("TRUE") : TEXT("FASLE"));
    UE_LOG(LogTemp, Warning, TEXT("%f"), DashCool);*/

    time += DeltaTime;


}
