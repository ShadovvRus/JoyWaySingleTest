#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "JoyWaySingleTest/Core/Enum/ItemClass.h"
#include "StructWeapon.generated.h"

class USoundBase;
class UAnimMontage;
class UMaterialInstance;
class USkeletalMesh;
USTRUCT(BlueprintType)
struct JOYWAYSINGLETEST_API FStructWeapon :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMesh* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInstance* WeaponMaterialInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* FireAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* ImageWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ProjectilesOnFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int AmmoInStore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CurrentAmmoInStore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EItemClass ClassAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Scatter;
};

