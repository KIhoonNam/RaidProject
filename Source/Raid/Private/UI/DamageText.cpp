// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageText.h"
#include "Actor.h"
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
void UDamageText::NativeConstruct()
{
	Super::NativeConstruct();

	if(DamageLabel)
		DamageLabel->SetText(FText::FromString(FString::FromInt(Damage)));

}

void UDamageText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ULocalPlayer* LP = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetLocalPlayer();
	LP->GetProjectionData(LP->ViewportClient->Viewport, eSSP_FULL, ProjectionData);
	FSceneView::ProjectWorldToScreen(Character->GetActorLocation(), ProjectionData.GetConstrainedViewRect(),
		ProjectionData.ComputeViewProjectionMatrix(), ScreenPos);
	this->SetPositionInViewport(ScreenPos + Position);

}
