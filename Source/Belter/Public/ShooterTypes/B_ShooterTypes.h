// Copyright Eduard Ciofu

#pragma once

#include "B_ShooterTypes.generated.h"

UENUM(BlueprintType)
enum class EB_TurningInPlace : uint8
{
	Left		UMETA(DisplayName = "Turning Left"),
	Right		UMETA(DisplayName = "Turning Right"),
	NotTurning	UMETA(DisplayName = "Not Turning"),
};