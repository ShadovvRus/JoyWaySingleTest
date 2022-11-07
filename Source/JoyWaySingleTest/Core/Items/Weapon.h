#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoyWaySingleTest/Core/Interface/InteractionObjectsInterface.h"
#include "JoyWaySingleTest/Core/Interface/InteractionWeaponInterface.h"
#include "JoyWaySingleTest/Core/Structs/StructWeapon.h"
#include "Weapon.generated.h"

class UDataTable;
class USkeletalMeshComponent;
class AProjectile;

enum class EWeaponClass : uint8;

UCLASS()
class JOYWAYSINGLETEST_API AWeapon : public AActor, public IInteractionWeaponInterface, public IInteractionObjectsInterface
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	UFUNCTION(CallInEditor)
		void Initialization(EWeaponClass Weapon);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWeaponClass WeaponClass;

protected:

	virtual void Fire() override;
	virtual void Reloading(float& Ammo) override;
	virtual bool TryInteract() override;
	virtual FStructWeapon GetWeapon() override;
	virtual void StateUpdate(FStructWeapon* Weapon) override;
	virtual void UpdateAddStatus(bool Flag) override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* WeaponDataTable= nullptr;

	void OnInitialization();

	FStructWeapon* StructWeapon;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* WeaponSkeletalMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* MuzzleStaticMesh = nullptr;

	float RandDeviation() const;

	FString GetNameByString(EWeaponClass Class) const;
};
