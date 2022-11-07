#include "Weapon.h"

#include "Animation/AnimInstance.h"
#include "JoyWaySingleTest/Core/Structs/StructWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "JoyWaySingleTest/Core/Character/PlayerCharacter.h"
#include "JoyWaySingleTest/Core/Enum/WeaponClass.h"
#include "JoyWaySingleTest/Core/Projectile/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

//DECLARE_LOG_CATEGORY_EXTERN(Weapon, Log, All);

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::Initialization(EWeaponClass Weapon)
{
	WeaponClass = Weapon;
	OnInitialization();
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	StructWeapon =new FStructWeapon;
	TSharedRef<FStructWeapon> TStructWeapon= MakeShareable(StructWeapon);

	Initialization(WeaponClass);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Fire()
{
	if (!WeaponSkeletalMesh) {return;}

	if (StructWeapon->CurrentAmmoInStore<=0) {return;}

	StructWeapon->CurrentAmmoInStore -= 1;

	const APawn* ControlledPawn=Cast<APawn>(GetAttachParentActor());
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	for (uint8 i = 0; i < StructWeapon->ProjectilesOnFire; ++i)
	{
		FVector ForwardVectorController=UKismetMathLibrary::GetForwardVector(ControlledPawn->GetControlRotation());
		ForwardVectorController = FVector(ForwardVectorController.X+ RandDeviation(), ForwardVectorController.Y+ RandDeviation(), ForwardVectorController.Z+ RandDeviation());
		FRotator FinalSpawnRotation=UKismetMathLibrary::MakeRotFromX(ForwardVectorController);

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleStaticMesh->GetComponentLocation(), FinalSpawnRotation, ActorSpawnParams);
		Projectile->SetDamage(StructWeapon->Damage);
	}

	if (StructWeapon->FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, StructWeapon->FireSound, GetActorLocation());
	}
}

void AWeapon::Reloading(float& Ammo)
{
	StructWeapon->CurrentAmmoInStore += Ammo;
	Ammo = 0;

	if (StructWeapon->CurrentAmmoInStore>StructWeapon->AmmoInStore)
	{
		Ammo = StructWeapon->CurrentAmmoInStore - StructWeapon->AmmoInStore;
		StructWeapon->CurrentAmmoInStore = StructWeapon->AmmoInStore;
	}
}

void AWeapon::OnInitialization()
{
	if (!WeaponDataTable) { return; }

	if (!WeaponSkeletalMesh)
	{
		WeaponSkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
	}

	if (!MuzzleStaticMesh)
	{
		MuzzleStaticMesh = FindComponentByClass<UStaticMeshComponent>();
	}

	StructWeapon = WeaponDataTable->FindRow<FStructWeapon>(FName(GetNameByString(WeaponClass)), "", true);

	if (!WeaponSkeletalMesh) {return;}

	WeaponSkeletalMesh->SetSkeletalMesh(StructWeapon->WeaponMesh);
	WeaponSkeletalMesh->SetMaterial(0, StructWeapon->WeaponMaterialInstance);
}


FString AWeapon::GetNameByString(EWeaponClass Class) const
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponClass"), true);

	if (EnumPtr)
	{
		return EnumPtr->GetNameStringByIndex(static_cast<int32>(Class));
	}

	UE_LOG(LogTemp, Warning, TEXT("(Weapon) GetNameByString: fail"));

	return FString("Invalid");
}

bool AWeapon::TryInteract()
{
	return true;
}

FStructWeapon AWeapon::GetWeapon()
{
	return *StructWeapon;
}

void AWeapon::StateUpdate(FStructWeapon* Weapon)
{
	StructWeapon = Weapon;

	if (!WeaponSkeletalMesh) { return; }

	WeaponSkeletalMesh->SetSkeletalMesh(StructWeapon->WeaponMesh);
	WeaponSkeletalMesh->SetMaterial(0, StructWeapon->WeaponMaterialInstance);
}

void AWeapon::UpdateAddStatus(bool Flag)
{
	if (Flag) { Destroy(); }
}

float AWeapon::RandDeviation() const
{
	return  FMath::RandRange(-StructWeapon->Scatter, StructWeapon->Scatter);
}



