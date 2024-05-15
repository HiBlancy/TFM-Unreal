// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickable.generated.h"

UCLASS()
class TOONTANKS_API APickable : public AActor
{
	GENERATED_BODY()
	
public:	
	APickable();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	class UCapsuleComponent* PickupBox;

};