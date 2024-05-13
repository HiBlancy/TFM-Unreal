// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankVanguardGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankVanguardGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:

	class APlayerPawn* Player;
	class ATankVanguardPlayerController* TankVanguardPlayerController;

	float StartDelay = 3.f;

	void HandelGameStart();

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();
};