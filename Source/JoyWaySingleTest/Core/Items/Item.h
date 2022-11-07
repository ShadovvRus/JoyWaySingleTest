// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoyWaySingleTest/Core/Interface/InteractionObjectsInterface.h"
#include "Item.generated.h"

enum class EItemClass : uint8;
UCLASS()
class JOYWAYSINGLETEST_API AItem : public AActor,public IInteractionObjectsInterface
{
	GENERATED_BODY()
	
public:

	AItem();

protected:

	UPROPERTY(EditAnywhere)
		EItemClass ItemClassEnum;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual bool TryInteract() override;
	virtual float GetValueItem(EItemClass& ItemClass) override;

	UPROPERTY(EditAnywhere)
	float ItemValue = 0.f;
private:

};
