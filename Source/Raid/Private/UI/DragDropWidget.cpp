// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DragDropWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Components/Progressbar.h>
#include <Components/TextBlock.h>

UDragDropWidget::UDragDropWidget()
{
	
}

void UDragDropWidget::SetPayLoad(UObject* _load)
{
	Payload = _load;
}