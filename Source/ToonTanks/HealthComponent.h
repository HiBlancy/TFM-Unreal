// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float MaxHealt = 100.f;
	float Health = 0.f;

	UFUNCTION()
	void DamegeTaken(
		AActor* DamagedActor, 
		float Damage, 
		const UDamageType* DamageType, 
		class AController* Instigator, 
		AActor* DamageCauser);

	class ATankVanguardGameMode* TankVanguardGameMode;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};