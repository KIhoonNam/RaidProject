// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExitButton.h"

#include <Raid/Public/UI/CustomUI.h>

#include <Components/Border.h>



FReply UExitButton::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonUp(MyGeometry, MouseEvent);


	if (MouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{

		ButtonCasting = true;
		return FReply::Handled();
	}
	else if (MouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{


	}
	return reply.NativeReply;
}

FReply UExitButton::NativeOnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonUp(MyGeometry, MouseEvent);


	if (ButtonCasting)
	{
		ButtonCasting = false;
		this->GetParent()->SetVisibility(ESlateVisibility::Collapsed);
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, this->GetParent()->GetParent()->GetName());

	}

	return FReply::Handled();
}