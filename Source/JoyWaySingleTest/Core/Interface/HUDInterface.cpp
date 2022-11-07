// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDInterface.h"

#include "JoyWaySingleTest/Core/Structs/StructWeapon.h"

// Add default functionality here for any IHUDInterface functions that are not pure virtual.

void IHUDInterface::TryInteractObject(bool bIsInteract)
{

}

void IHUDInterface::UpdateAmmoInStore(int Ammo)
{
}

void IHUDInterface::UpdateAmmoInInventory(int Ammo)
{
}

void IHUDInterface::UpdateHealPoint(float HP)
{
}

void IHUDInterface::UpdateActiveItemSlot(uint8 ActiveSlot)
{
}

void IHUDInterface::UpdateDataWeaponSlots(TMap<uint8, FStructWeapon>* ArrWeapons)
{
}
