// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWeaponInterface.h"
#include "JoyWaySingleTest/Core/Structs/StructWeapon.h"

void IInteractionWeaponInterface::Fire()
{
	
}

void IInteractionWeaponInterface::Reloading(float& Ammo)
{

}

FStructWeapon IInteractionWeaponInterface::GetWeapon()
{
	return {};
}

void IInteractionWeaponInterface::StateUpdate(FStructWeapon* Weapon)
{
}

void IInteractionWeaponInterface::UpdateAddStatus(bool Flag)
{
}
