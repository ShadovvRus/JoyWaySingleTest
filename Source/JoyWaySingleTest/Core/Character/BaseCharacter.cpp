// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "JoyWaySingleTest/Core/Interface/HUDInterface.h"
#include "Kismet/KismetMathLibrary.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::OnDamage);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	FirstPersonController = NewController;

	CalculatePercentHealPoint();
}

void ABaseCharacter::AddHealPoint(float HP)
{
	CurrentHealPoint + HP >= MaxHealPoint ? CurrentHealPoint = MaxHealPoint : CurrentHealPoint += HP;

	CalculatePercentHealPoint();
}

void ABaseCharacter::OnDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealPoint -= Damage;

	CalculatePercentHealPoint();

	if (CurrentHealPoint <= 0) { Destroy(); }
}

void ABaseCharacter::CalculatePercentHealPoint()
{
	PercentHealPoint = UKismetMathLibrary::NormalizeToRange(CurrentHealPoint, 0.f, MaxHealPoint);

	IHUDInterface* HUDInterface = Cast<IHUDInterface>(FirstPersonController);

	if (HUDInterface)
	{
		HUDInterface->UpdateHealPoint(PercentHealPoint);
	}
}






