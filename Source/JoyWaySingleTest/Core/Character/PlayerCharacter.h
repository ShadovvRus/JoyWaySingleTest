// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UInventoryComponent;
class UCameraComponent;

UCLASS()
class JOYWAYSINGLETEST_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:

	APlayerCharacter();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Destroyed() override;

private:

	UPROPERTY()
	TArray<AActor*> ChildActor{};

	UPROPERTY()
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY()
	UInventoryComponent* InventoryComponent = nullptr;

	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnTurn(float Axis);
	void OnLookUp(float Axis);
	void OnFire();
	void OnInteraction();
	void OnReloading();
	void OnFirstSlot();
	void OnSecondSlot();
	void OnThirdSlot();
	void OnFourthSlot();
	void OnFifthSlot();

	void JumpPressed();
	void JumpReleased();

	void StateUpdateWeapon(uint8 Slot);
};
