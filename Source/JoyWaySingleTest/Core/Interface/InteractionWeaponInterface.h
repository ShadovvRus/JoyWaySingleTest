// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionWeaponInterface.generated.h"

struct FStructWeapon;
UINTERFACE(MinimalAPI)
class UInteractionWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class JOYWAYSINGLETEST_API IInteractionWeaponInterface
{
	GENERATED_BODY()

public:

	virtual void Fire();
	virtual void Reloading(float& Ammo);
	virtual FStructWeapon GetWeapon();
	virtual void StateUpdate(FStructWeapon* Weapon);
	virtual void UpdateAddStatus(bool Flag);
};
