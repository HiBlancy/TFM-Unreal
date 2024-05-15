// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEnemyPawn::AEnemyPawn()
{
	CurrentAmmo = 35;
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Ditancia del jugador
	if (InFireRange())
	{
		RotateTurret(Player->GetActorLocation());
	}
}

void AEnemyPawn::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0)); 
	//castearlo porque como el enemigo es hijo de BasePawn, no puede almacenar puntero tipo padre el hijo

	GetWorldTimerManager().SetTimer(FireRateTimerHandel, this, &AEnemyPawn::CheckFireCondition, FireRate, true);
}

void AEnemyPawn::CheckFireCondition()
{
	if (Player == nullptr)
	{
		return;
	}

	if (InFireRange() && Player->bAlive)
	{
		Fire();
	}
}


bool AEnemyPawn::InFireRange()
{
	if(Player)
	{
		float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}