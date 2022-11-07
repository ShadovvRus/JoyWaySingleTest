// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "JoyWaySingleTest/Core/Enum/ItemClass.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int8 i=0;i<=MaxKey;++i)
	{
		ArrSlotsWeapon.Add(i,{});
	}
}

void UInventoryComponent::AddAmmo(const EItemClass& ItemClass, float AmmoValue)
{
	switch (ItemClass)
	{
	case EItemClass::AmmoPistol:
		{
			AmmoPistol += AmmoValue;
			break;
		}
	case EItemClass::AmmoShotgun:
		{
			AmmoGunshot += AmmoValue;
			break;
		}
	default: break;
	}
}

float& UInventoryComponent::GetAmmo()
{
	if (ArrSlotsWeapon.Num() == 0) { return Other; }

	switch (ArrSlotsWeapon.Find(InteractionKey)->ClassAmmo)
	{
	case EItemClass::AmmoPistol:
	{
		return  AmmoPistol;
	}
	case EItemClass::AmmoShotgun:
	{
		return AmmoGunshot;
	}
	default: return Other;
	}
	
}

FStructWeapon* UInventoryComponent::GetWeaponBySlot(uint8 Slot)
{
	if (Slot>MaxKey)
	{
		return nullptr;
	}

	InteractionKey = Slot;

	return ArrSlotsWeapon.Find(Slot);
}

bool UInventoryComponent::AddWeapon(FStructWeapon StructWeapon)
{
	if (CurrentKey<MaxKey)
	{
		ArrSlotsWeapon.Add(CurrentKey,StructWeapon);
		++CurrentKey;

		return true;
	}

	return false;
}

FStructWeapon* UInventoryComponent::GetActiveSlot()
{
	return ArrSlotsWeapon.Find(InteractionKey);;
}

TMap<uint8, FStructWeapon>* UInventoryComponent::GetArrSlotsWeapon()
{
	return &ArrSlotsWeapon;
}


