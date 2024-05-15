// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletPickable.h"
#include "PlayerPawn.h"

void ABulletPickable::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnterPickupBox(OverlapedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

	if (Player)
	{
		int32 NumAmmo = FMath::RandRange(2, 15); //Random entre 2 y 15 para que el drop de balas varie
			
		Player->GiveBullets(NumAmmo);

		UE_LOG(LogTemp, Warning, TEXT("Gived %d of ammo"), NumAmmo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Bullets found on the player"));
	}
}