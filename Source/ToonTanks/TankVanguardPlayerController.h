// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankVanguardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankVanguardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void SetPlayerEnabledState(bool bPlayerEnabled);

	virtual void SetupInputComponent() override;

	void RestartGame();
};