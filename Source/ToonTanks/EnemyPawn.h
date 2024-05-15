// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()
	

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class APlayerPawn* Player;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float FireRange = 1000.f;

	FTimerHandle FireRateTimerHandel;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();
};