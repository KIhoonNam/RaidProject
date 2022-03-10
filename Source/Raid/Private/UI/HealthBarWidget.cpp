// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"
#include <Raid/Public/Character/MyCharacter.h>
#include <Raid/Public/UI/DragDropWidget.h>
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Blueprint/DragDropOperation.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	HealthBar->SetPercent(Player->GetCurrentHp() / Player->GetMaxHp());

	CurrentHealthLabel->SetText(FText::FromString(FString::FromInt(Player->GetCurrentHp())));
	MaxHealthLabel->SetText(FText::FromString(FString::FromInt(Player->GetMaxHp())));

	ManaBar->SetPercent(Player->GetCurrentMp() / Player->GetMaxMp());

	CurrentManaLabel->SetText(FText::FromString(FString::FromInt(Player->GetCurrentMp())));
	MaxManaLabel->SetText(FText::FromString(FString::FromInt(Player->GetMaxMp())));


	
}
//
//FReply UHealthBarWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	FEventReply reply;
//	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//
//	reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
//
//
//
//	return reply.NativeReply;
//}
//void UHealthBarWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
//{
//	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
//
//	UDragDropWidget* WidgetDD = Cast<UDragDropWidget>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropWidget::StaticClass()));
//
//	if (WidgetDD == nullptr) return;
//	WidgetDD->SetPayLoad(QSkillBar->WidgetStyle.BackgroundImage.GetResourceObject());
//	WidgetDD->Offset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
//	WidgetDD->DefaultDragVisual = this;
//	WidgetDD->Pivot = EDragPivot::MouseDown;
//	OutOperation = WidgetDD;
//
//
//	this->RemoveFromParent();
//	if (GEngine)
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Drag"));
//}
