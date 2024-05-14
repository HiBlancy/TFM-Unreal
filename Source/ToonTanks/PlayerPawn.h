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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
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

	//AMMO
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 ExcessAmmo;


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
};
