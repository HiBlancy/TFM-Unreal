// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickable.h"
#include "BulletPickable.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ABulletPickable : public APickable
{
	GENERATED_BODY()


protected:

	virtual void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
