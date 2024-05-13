// Fill out your copyright notice in the Description page of Project Settings.


#include "TankVanguardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "EnemyPawn.h"
#include "TankVanguardPlayerController.h"
#include "TimerManager.h"

void ATankVanguardGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Player)
	{
		Player->HandleDestruction();
		if (TankVanguardPlayerController)
		{
			TankVanguardPlayerController->SetPlayerEnabledState(false);
		}		
		GameOver(false);
	}
	else if (AEnemyPawn* DestroyedTower = Cast<AEnemyPawn>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers == 0)
		{
			GameOver(true); //Termina el juego en que tu ganas
		}
	}

	FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &ATankVanguardGameMode::BeginPlay);
}

void ATankVanguardGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandelGameStart();
}

void ATankVanguardGameMode::HandelGameStart()
{
	TargetTowers = GetTargetTowerCount();
	
	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	TankVanguardPlayerController = Cast<ATankVanguardPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	/*Castear = convertir una referencia de un tipo a otro tipo relacionado, generalmente utilizado para realizar 
	comprobaciones de tipo y acceder a funcionalidades especificas de ese tipo en Player accede a la funcion de GetPlayerPawn*/

	StartGame();

	if (TankVanguardPlayerController)
	{
		TankVanguardPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			TankVanguardPlayerController,
			&ATankVanguardPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}
}

int32 ATankVanguardGameMode::GetTargetTowerCount()
{
	TArray<AActor*> EnemyTurrets;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemyPawn::StaticClass(), EnemyTurrets);
	return EnemyTurrets.Num();


}