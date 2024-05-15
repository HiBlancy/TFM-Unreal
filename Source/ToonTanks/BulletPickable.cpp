// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletPickable.h"
#include "PlayerPawn.h"

void ABulletPickable::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnterPickupBox(OverlapedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

		UE_LOG(LogTemp, Warning, TEXT("THIS IS Bullets!"));

		if (APlayerPawn* Player = Cast<APlayerPawn>(OtherActor))
		{
			Player->GiveBullets(5);
		}
}