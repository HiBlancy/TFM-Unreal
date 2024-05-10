// Fill out your copyright notice in the Description page of Project Settings.


#include "TankVanguardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "EnemyPawn.h"

void ATankVanguardGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandeDestruction();
		if (Tank->GetTankPlayerController())
		{
			Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}		
	}
	else if (AEnemyPawn* DestroyedTower = Cast<AEnemyPawn>(DeadActor))
	{
		DestroyedTower->HandeDestruction();
	}
}

void ATankVanguardGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}