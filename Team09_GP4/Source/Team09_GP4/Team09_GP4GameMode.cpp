// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team09_GP4GameMode.h"
#include "Team09_GP4Character.h"
#include "UObject/ConstructorHelpers.h"

ATeam09_GP4GameMode::ATeam09_GP4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
