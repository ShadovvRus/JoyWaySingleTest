#pragma once

#include "Engine/UserDefinedEnum.h"
#include "WeaponClass.generated.h"

UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
	Empty	UMETA(DisplayName = "None"),
	Pistol  UMETA(DisplayName="Pistol"),
	Shotgun UMETA(DisplayName="Shotgun")
};
