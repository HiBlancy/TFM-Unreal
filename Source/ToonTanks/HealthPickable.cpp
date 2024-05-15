// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickable.h"
#include "HealthComponent.h"
#include "PlayerPawn.h"

void AHealthPickable::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnterPickupBox(OverlapedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		
	UE_LOG(LogTemp, Warning, TEXT("THIS IS HEALTH!"));

	UHealthComponent* HealthNum = OtherActor->FindComponentByClass<UHealthComponent>();
	if (HealthNum)
	{
		HealthNum->GiveHealth(15.f);
		UE_LOG(LogTemp, Warning, TEXT("Entering the function"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Health Component found on the player!"));
	}
}