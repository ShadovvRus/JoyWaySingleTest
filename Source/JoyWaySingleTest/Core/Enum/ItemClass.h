#pragma once

#include "Engine/UserDefinedEnum.h"
#include "ItemClass.generated.h"

UENUM(BlueprintType)
enum class EItemClass : uint8
{
	Heal	    UMETA(DisplayName = "Heal"),
	AmmoPistol  UMETA(DisplayName = "AmmoPistol"),
	AmmoShotgun UMETA(DisplayName = "AmmoShotgun")
};
