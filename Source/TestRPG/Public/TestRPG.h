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
