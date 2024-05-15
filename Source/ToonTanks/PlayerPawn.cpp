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

	CurrentAmmo = 12;
	MaxAmmo = 12;
	ExcessAmmo = 8;
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
		FHitResult HitResult; //Variable para almacenar info sobre un impacto
		PlayerController->GetHitResultUnderCursor( //obtener info sobre el inpacto bajo la posicion del cursor
			ECollisionChannel::ECC_Visibility, //canal de colision que se utiliza para realizar la deteccion de impacto, solo los visibles
			false, //si fuera true el trazado de rayos considerara ibjetos de colision, false es solo para objetos visibles
			HitResult); //donde se almacenaa la info sobre el impacto

		RotateTurret(HitResult.ImpactPoint);
	}
}

void APlayerPawn::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	
	InputComponent->BindAction(
		"Reload", //Nombre asignado desde el editor de la tecla
		IE_Pressed, //Cuando se presiona
		this, //Esto
		&APlayerPawn::Reload); //Llama a esta funcion 
}

void APlayerPawn::Reload()
{
	int32 MissingAmmo = MaxAmmo - CurrentAmmo;
	if (MissingAmmo > 0)
	{
		int32 ReloadAmount = FMath::Min(MissingAmmo, ExcessAmmo);
		CurrentAmmo += ReloadAmount;
		ExcessAmmo -= ReloadAmount;

		UE_LOG(LogTemp, Warning, TEXT("Reloaded %d bullets"), ReloadAmount);
		UE_LOG(LogTemp, Warning, TEXT("You have %d more bullets"), ExcessAmmo);
		UE_LOG(LogTemp, Warning, TEXT("Current %d bullets"), CurrentAmmo);
	}
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