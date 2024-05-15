// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickable.h"
#include "HealthComponent.h"

void AHealthPickable::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnterPickupBox(OverlapedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UHealthComponent* HealthNum = OtherActor->FindComponentByClass<UHealthComponent>();
	if (HealthNum)
	{
		float NumHealth = FMath::RandRange(2.f, 50.f);

		HealthNum->GiveHealth(NumHealth);
		UE_LOG(LogTemp, Warning, TEXT("Gived %f health"), NumHealth);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Health Component found on the player!"));
	}
}