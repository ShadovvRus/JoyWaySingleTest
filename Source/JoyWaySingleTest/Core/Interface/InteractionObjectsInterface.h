// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionObjectsInterface.generated.h"

enum class EItemClass : uint8;

UINTERFACE(MinimalAPI)
class UInteractionObjectsInterface : public UInterface
{
	GENERATED_BODY()
};

class JOYWAYSINGLETEST_API IInteractionObjectsInterface
{
	GENERATED_BODY()

public:

	virtual bool TryInteract();
	virtual float GetValueItem(EItemClass& ItemClass);
};
