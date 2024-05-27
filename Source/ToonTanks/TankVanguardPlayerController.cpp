// Fill out your copyright notice in the Description page of Project Settings.


#include "TankVanguardPlayerController.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.h"
#include <Kismet/GameplayStatics.h>

void ATankVanguardPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled) //la letra b delante del PlayerEnabled indica que es un booleando
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}

void ATankVanguardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind the RestartGame action
	InputComponent->BindAction(TEXT("RestartGame"), IE_Pressed, this, &ATankVanguardPlayerController::RestartGame);
}

void ATankVanguardPlayerController::RestartGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FName MainMenuMap = *World->GetName();
		UGameplayStatics::OpenLevel(this, MainMenuMap);
	}
}