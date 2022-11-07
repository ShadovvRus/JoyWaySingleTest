// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayerController.h"


void AFirstPersonPlayerController::TryInteractObject(const bool bIsInteract)
{
	EventTryInteractObject(bIsInteract);
}

void AFirstPersonPlayerController::UpdateAmmoInStore(const int Ammo)
{
	EventUpdateAmmoInStore(Ammo);
}

void AFirstPersonPlayerController::UpdateAmmoInInventory(const int Ammo)
{
	EventUpdateAmmoInInventory(Ammo);
}

void AFirstPersonPlayerController::UpdateHealPoint(float HP)
{
	EventUpdateHealPoint(HP);
}

void AFirstPersonPlayerController::UpdateActiveItemSlot(uint8 ActiveSlot)
{
	EventUpdateItemSlot(ActiveSlot);
}

void AFirstPersonPlayerController::UpdateDataWeaponSlots(TMap<uint8, FStructWeapon>* ArrWeapons)
{
	EventUpdateDataWeaponSlots(*ArrWeapons);
}




