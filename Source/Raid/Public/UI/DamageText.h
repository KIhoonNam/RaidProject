// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageText.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UDamageText : public UUserWidget
{
	GENERATED_BODY()
public:
	void GetActor(AActor* _character) { Character = _character; }

	void SetDamage(float _damage) { Damage = _damage; }

	void SetPosition(FVector2D _position) { Position = _position; }

protected:
	class AActor* Character;

	virtual void NativeConstruct() override;


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* DamageLabel;

	FVector2D ScreenPos;
	FSceneViewProjectionData ProjectionData;
	FVector2D Position;
	int Damage;
};
