// Fill out your copyright notice in the Description page of Project Settings.


#include "TankVanguardPlayerController.h"
#include "GameFramework/Pawn.h"

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