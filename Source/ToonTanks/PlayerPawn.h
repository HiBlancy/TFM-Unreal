// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()


public:
	APlayerPawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetPlayerController() const 
	{
		return PlayerController;
	}

	bool bAlive = true;

	void Reload();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MaxAmmo;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Movment")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movment")
	float TurnRate = 45.f;
	
	void Move(float Value);
	void Turn(float Value);

	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* ReloadSound;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 ExcessAmmo;

	UFUNCTION()
	void GiveBullets(int32 AmmoAmount);
};
