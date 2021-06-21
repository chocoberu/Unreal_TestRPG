// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterAffiliation : uint8
{
	E_Player = 0 UMETA(DisplayName = "Player"),
	E_Enemy UMETA(DisplayName = "Enemy"),
	E_Neutral UMETA(DIsplayName = "Neutral"),
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	E_Idle = 0 UMETA(DisplayName = "Idle"),
	E_Entrance UMETA(DisplayName = "Entrance"),
	E_Patrol UMETA(DisplayName = "Patrol"),
	E_Chasing UMETA(DisplayName = "Chasing"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Skill UMETA(DisplayName = "Skill"),
	E_Dead UMETA(DisplayName = "Dead"),
};