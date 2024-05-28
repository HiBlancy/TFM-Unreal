// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletPickable.h"
#include "PlayerPawn.h"

ABulletPickable::ABulletPickable()
{
	PickupMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh2"));
	PickupMesh2->SetupAttachment(PickupMesh);

	PickupMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh3"));
	PickupMesh3->SetupAttachment(PickupMesh);
}

void ABulletPickable::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnterPickupBox(OverlapedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

	if (Player)
	{
		int32 NumAmmo = FMath::RandRange(3, 9); //Random entre 3 y 9 para que el drop de balas varie
			
		Player->GiveBullets(NumAmmo);

		UE_LOG(LogTemp, Warning, TEXT("Gived %d of ammo"), NumAmmo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Bullets found on the player"));
	}
}