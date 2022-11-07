// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JoyWayGameMode.generated.h"

class APlayerCharacter;
UCLASS()
class JOYWAYSINGLETEST_API AJoyWayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void RespawnPlayer(APlayerController* PlayerController);

private:
};
