// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CustomUI.h"
#include "SkillUI.generated.h"

class UListView;

/**
 * 
 */
UCLASS()
class RAID_API USkillUI : public UCustomUI
{
	GENERATED_BODY()
public:
	void Init();

protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		UListView* SkillList;
};
