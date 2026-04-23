// Copyright Epic Games, Inc. All Rights Reserved.

#include "NBC_UA_HW02GameMode.h"
#include "NBC_UA_HW02Character.h"
#include "UObject/ConstructorHelpers.h"

ANBC_UA_HW02GameMode::ANBC_UA_HW02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
