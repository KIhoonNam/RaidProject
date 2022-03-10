// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Runtime/Core/Public/UObject/NameTypes.h>
#include <Runtime/Core/Public/Containers/UnrealString.h>

namespace bb_Keys
{
	TCHAR const* const target_location = TEXT("TargetLocation");
	TCHAR const* const home_location = TEXT("HomePosKey");
	TCHAR const* const can_see_player = TEXT("CanSeePlayer");
	TCHAR const* const player_is_in_melee_range = TEXT("IsPlayerInMeRange");
	TCHAR const* const enemy_range_over = TEXT("EnemyRangeOver");
	TCHAR const* const player_object = TEXT("PlayerObject");
	TCHAR const* const attack_check = TEXT("AttackCheck");	
}

/**
 * 
 */
class RAID_API BlackBoard_Keys
{
public:
	BlackBoard_Keys();
	~BlackBoard_Keys();
};
