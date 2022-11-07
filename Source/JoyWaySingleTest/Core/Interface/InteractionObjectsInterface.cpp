// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionObjectsInterface.h"

// Add default functionality here for any IInteractionObjectsInterface functions that are not pure virtual.

bool IInteractionObjectsInterface::TryInteract()
{
	return false;
}

float IInteractionObjectsInterface::GetValueItem(EItemClass& ItemClass)
{
	return 0.f;
}
