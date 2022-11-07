// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "JoyWaySingleTest/Core/Interface/InteractionWeaponInterface.h"
#include "JoyWaySingleTest/Core/Components/InventoryComponent.h"
#include "JoyWaySingleTest/Core/Structs/StructWeapon.h"
#include "JoyWaySingleTest/Core/GameMode/JoyWayGameMode.h"
#include "JoyWaySingleTest/Core/Interface/HUDInterface.h"
#include "JoyWaySingleTest/Core/Items/Item.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const UWorld* World = GetWorld();

	if (!World) { return; }

	World->LineTraceSingleByChannel(HitResult,
		CameraComponent->GetComponentLocation(),
		CameraComponent->GetComponentLocation()+ CameraComponent->GetForwardVector()*200.f,
		ECollisionChannel::ECC_Visibility);

	IInteractionObjectsInterface* InteractionObjectsInterface =Cast<IInteractionObjectsInterface>(HitResult.GetActor());
	IHUDInterface* HUDInterface=Cast<IHUDInterface>(FirstPersonController);

	if (!HUDInterface) {return;}

	if (!InteractionObjectsInterface)
	{
		HUDInterface->TryInteractObject(false);

		return;
	}

	InteractionObjectsInterface->TryInteract() ? HUDInterface->TryInteractObject(true) : HUDInterface->TryInteractObject(false);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APlayerCharacter::OnTurn);
	PlayerInputComponent->BindAxis("LookUp",this,&APlayerCharacter::OnLookUp);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&APlayerCharacter::JumpPressed);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APlayerCharacter::JumpReleased);
	PlayerInputComponent->BindAction("Fire", IE_Pressed,this,&APlayerCharacter::OnFire);
	PlayerInputComponent->BindAction("Interaction",IE_Pressed,this,&APlayerCharacter::OnInteraction);
	PlayerInputComponent->BindAction("Reloading",IE_Pressed,this,&APlayerCharacter::OnReloading);
	PlayerInputComponent->BindAction("First Slot",IE_Pressed,this,&APlayerCharacter::OnFirstSlot);
	PlayerInputComponent->BindAction("Second slot",IE_Pressed,this,&APlayerCharacter::OnSecondSlot);
	PlayerInputComponent->BindAction("Third Slot", IE_Pressed, this, &APlayerCharacter::OnThirdSlot);
	PlayerInputComponent->BindAction("Fourth Slot", IE_Pressed, this, &APlayerCharacter::OnFourthSlot);
	PlayerInputComponent->BindAction("Fifth slot", IE_Pressed, this, &APlayerCharacter::OnFifthSlot);

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetAllChildActors(ChildActor, true);

	CameraComponent = FindComponentByClass<UCameraComponent>();
	InventoryComponent = FindComponentByClass<UInventoryComponent>();
}

void APlayerCharacter::Destroyed()
{
	AJoyWayGameMode* GameMode = Cast<AJoyWayGameMode>(GetWorld()->GetAuthGameMode());
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (!PlayerController) {return;} 

	GameMode->RespawnPlayer(PlayerController);

}

void APlayerCharacter::OnMoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void APlayerCharacter::OnMoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}

void APlayerCharacter::OnTurn(float Axis)
{
	AddControllerYawInput(Axis);
}

void APlayerCharacter::OnLookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

void APlayerCharacter::OnFire()
{
	if (!ChildActor.GetData()) {return;}
	
	IInteractionWeaponInterface* InteractionWeaponInterface = Cast<IInteractionWeaponInterface>(ChildActor[0]);
	InteractionWeaponInterface->Fire();

	IHUDInterface* HUDInterface = Cast<IHUDInterface>(FirstPersonController);

	if (!HUDInterface) { return; }

	HUDInterface->UpdateAmmoInStore(InventoryComponent->GetActiveSlot()->CurrentAmmoInStore);
	
}

void APlayerCharacter::JumpPressed()
{
	Jump();
}

void APlayerCharacter::JumpReleased()
{
	StopJumping();
}

void APlayerCharacter::StateUpdateWeapon(uint8 Slot)
{
	FStructWeapon* Weapon = InventoryComponent->GetWeaponBySlot(Slot);

	if (!ChildActor.GetData()) {return;}

	IHUDInterface* HUDInterface=Cast<IHUDInterface>(FirstPersonController);

	IInteractionWeaponInterface* InteractionWeaponInterface = Cast<IInteractionWeaponInterface>(ChildActor[0]);
	InteractionWeaponInterface->StateUpdate(Weapon);

	if (!HUDInterface) {return;}

	HUDInterface->UpdateAmmoInInventory(InventoryComponent->GetAmmo());
	HUDInterface->UpdateAmmoInStore(InventoryComponent->GetActiveSlot()->CurrentAmmoInStore);
	HUDInterface->UpdateActiveItemSlot(Slot);
	
}

void APlayerCharacter::OnInteraction()
{
	FHitResult HitResult{};

	GetWorld()->LineTraceSingleByChannel(HitResult,
		CameraComponent->GetComponentLocation(),
		CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 200.f,
		ECollisionChannel::ECC_Visibility);

	IInteractionObjectsInterface* const InteractionObjectsInterface = Cast<IInteractionObjectsInterface>(HitResult.GetActor());
	IInteractionWeaponInterface* const InteractionWeaponInterface = Cast<IInteractionWeaponInterface>(HitResult.GetActor());

	EItemClass ItemClass{};
	float Value = 0;

	if (InteractionObjectsInterface)
	{
		Value = InteractionObjectsInterface->GetValueItem(ItemClass);
	}

	if (ItemClass == EItemClass::Heal)
	{
		AddHealPoint(Value);
	}
	
	if (!InventoryComponent) { return; }

	InventoryComponent->AddAmmo(ItemClass, Value);
	IHUDInterface* HUDInterface = Cast<IHUDInterface>(FirstPersonController);

	if (InteractionWeaponInterface)
	{
		const bool flag=InventoryComponent->AddWeapon(InteractionWeaponInterface->GetWeapon());
		InteractionWeaponInterface->UpdateAddStatus(flag);
	}

	if (HUDInterface)
	{
		HUDInterface->UpdateAmmoInInventory(InventoryComponent->GetAmmo());
		HUDInterface->UpdateDataWeaponSlots(InventoryComponent->GetArrSlotsWeapon());
	}
}

void APlayerCharacter::OnReloading()
{
	if (!ChildActor.GetData()) {return;}
		
	IInteractionWeaponInterface* InteractionWeaponInterface = Cast<IInteractionWeaponInterface>(ChildActor[0]);

	if (!InventoryComponent) {return;} 

	InteractionWeaponInterface->Reloading(InventoryComponent->GetAmmo());
	IHUDInterface* HUDInterface = Cast<IHUDInterface>(FirstPersonController);

	if (HUDInterface)
	{
		HUDInterface->UpdateAmmoInInventory(InventoryComponent->GetAmmo());
		HUDInterface->UpdateAmmoInStore(InventoryComponent->GetActiveSlot()->CurrentAmmoInStore);
	}
}

void APlayerCharacter::OnFirstSlot()
{
	StateUpdateWeapon(0);
}

void APlayerCharacter::OnSecondSlot()
{
	StateUpdateWeapon(1);
}

void APlayerCharacter::OnThirdSlot()
{
	StateUpdateWeapon(2);
}

void APlayerCharacter::OnFourthSlot()
{
	StateUpdateWeapon(3);
}

void APlayerCharacter::OnFifthSlot()
{
	StateUpdateWeapon(4);
}




