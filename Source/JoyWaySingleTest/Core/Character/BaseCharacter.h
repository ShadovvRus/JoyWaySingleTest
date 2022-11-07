#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class JOYWAYSINGLETEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:

	float MaxHealPoint = 100.f;
	float CurrentHealPoint = 50.f;
	float PercentHealPoint = 0.f;

	UPROPERTY()
		AController* FirstPersonController = nullptr;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

	void AddHealPoint(float HP);

private:
	UFUNCTION()
	void OnDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void CalculatePercentHealPoint();

};
