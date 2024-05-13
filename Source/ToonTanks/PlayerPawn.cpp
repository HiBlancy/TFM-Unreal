// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

APlayerPawn::APlayerPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArm);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::Move);//Movieminto del jugar
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerPawn::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::Fire); //Disparo del jugador
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, 
			false, 
			HitResult);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void APlayerPawn::HandleDestruction()
{
	Super::HandeDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
}

void APlayerPawn::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;	
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); //DeltaTime para movimiento FPS independiente
	AddActorLocalOffset(DeltaLocation, true); //true fot Sweeping
}

void APlayerPawn::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this); 
	AddActorLocalRotation(DeltaRotation, true);
}