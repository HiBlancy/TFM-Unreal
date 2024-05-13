// Fill out your copyright notice in the Description page of Project Settings.


#include "TankVanguardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "EnemyPawn.h"

void ATankVanguardGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Player)
	{
		Player->HandeDestruction();
		if (Player->GetPlayerController())
		{
			Player->DisableInput(Player->GetPlayerController());
			Player->GetPlayerController()->bShowMouseCursor = false;
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

	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}