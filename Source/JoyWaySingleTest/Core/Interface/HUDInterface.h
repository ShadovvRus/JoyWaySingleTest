// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

struct FStructWeapon;

UINTERFACE(MinimalAPI)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class JOYWAYSINGLETEST_API IHUDInterface
{
	GENERATED_BODY()

public:

	virtual void TryInteractObject(bool bIsInteract);
	virtual void UpdateAmmoInStore(int Ammo);
	virtual void UpdateAmmoInInventory(int Ammo);
	virtual void UpdateHealPoint(float HP);
	virtual void UpdateActiveItemSlot(uint8 ActiveSlot);
	virtual void UpdateDataWeaponSlots(TMap<uint8, FStructWeapon>* ArrWeapons);

};
