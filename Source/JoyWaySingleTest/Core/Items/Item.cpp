// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "JoyWaySingleTest/Core/Enum/ItemClass.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AItem::TryInteract()
{
	return true;
}

float AItem::GetValueItem(EItemClass& ItemClass)
{
	ItemClass = ItemClassEnum;

	Destroy();

	return ItemValue;
}

