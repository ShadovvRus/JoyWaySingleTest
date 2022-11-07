// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JoyWaySingleTest/Core/Structs/StructWeapon.h"
#include "InventoryComponent.generated.h"


enum class EItemClass : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOYWAYSINGLETEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventoryComponent();

	void AddAmmo(const EItemClass& ItemClass,float AmmoValue);
	float& GetAmmo();
	FStructWeapon* GetWeaponBySlot(uint8 Slot);
	bool AddWeapon(FStructWeapon StructWeapon);
	FStructWeapon* GetActiveSlot();
	TMap<uint8, FStructWeapon>* GetArrSlotsWeapon();

protected:

	virtual void BeginPlay() override;

private:

	float AmmoPistol = 0.f;
	float AmmoGunshot = 0.f;
	float Other = 0.f;

	uint8 CurrentKey = 0;
	uint8 MaxKey = 5;
	uint8 InteractionKey = 0;

	UPROPERTY()
	TMap<uint8,FStructWeapon> ArrSlotsWeapon;

};
