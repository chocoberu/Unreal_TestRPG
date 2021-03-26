// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestRPGGameMode.h"
#include "TestRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestRPGGameMode::ATestRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
