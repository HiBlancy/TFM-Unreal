// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEnemyPawn::AEnemyPawn()
{
	CurrentAmmo = 50;
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

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0)); 
	//castearlo porque como el enemigo es hijo de BasePawn, no puede almacenar puntero tipo padre el hijo

	GetWorldTimerManager().SetTimer(FireRateTimerHandel, this, &AEnemyPawn::CheckFireCondition, FireRate, true);
}

void AEnemyPawn::HandleDestruction()
{
	Super::HandleDestruction();

	HandleDrop();
	Destroy();
}

void AEnemyPawn::HandleDrop()
{
	if (FMath::RandRange(0.0f, 1.0f) <= DropProbability && DropItemClasses.Num() > 0) //random de ver si spawnear o no el item
	{
		int32 RandomIndex = FMath::RandRange(0, DropItemClasses.Num() - 1);
		TSubclassOf<AActor> SelectedDropItemClass = DropItemClasses[RandomIndex]; //eligue entre los pickables que hay
		if (SelectedDropItemClass) //una vez seleccionado el pickable lo spawnea el la localizacion del enmigo
		{
			FVector Location = GetActorLocation();
			FRotator Rotation = GetActorRotation();
			GetWorld()->SpawnActor<AActor>(SelectedDropItemClass, Location, Rotation);
		}
		//establezco desde el blueprint sus colision con overlap all o no collisions, pero como hago que ignore al enemigo pero al jugador no
	}
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