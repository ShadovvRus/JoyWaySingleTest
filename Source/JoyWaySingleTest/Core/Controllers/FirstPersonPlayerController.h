// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JoyWaySingleTest/Core/Structs/StructWeapon.h"
#include "JoyWaySingleTest/Core/Interface/HUDInterface.h"
#include "FirstPersonPlayerController.generated.h"

UCLASS()
class JOYWAYSINGLETEST_API AFirstPersonPlayerController : public APlayerController, public  IHUDInterface
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void EventTryInteractObject(bool bIsInteract);
	UFUNCTION(BlueprintImplementableEvent)
	void EventUpdateAmmoInStore(int Ammo);
	UFUNCTION(BlueprintImplementableEvent)
	void EventUpdateAmmoInInventory(int Ammo);
	UFUNCTION(BlueprintImplementableEvent)
	void EventUpdateHealPoint(float HP);
	UFUNCTION(BlueprintImplementableEvent)
	void EventUpdateItemSlot(uint8 ActiveSlot);
	UFUNCTION(BlueprintImplementableEvent)
	void EventUpdateDataWeaponSlots(const TMap<uint8, FStructWeapon>& ArrWeapons);

private:

	virtual void TryInteractObject(bool bIsInteract) override;
	virtual void UpdateAmmoInStore(int Ammo) override;
	virtual void UpdateAmmoInInventory(int Ammo) override;
	virtual void UpdateHealPoint(float HP) override;
	virtual void UpdateActiveItemSlot(uint8 ActiveSlot) override;
	virtual void UpdateDataWeaponSlots(TMap<uint8, FStructWeapon>* ArrWeapons) override;
};
