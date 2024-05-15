// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankVanguardGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealt;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamegeTaken);
	//AddDynamics = controlador de eventos dinamico al evento OnTakeAnyDamage, y cuando este se activa llama al metodo de la clase asignada
	//GetOwner = obtiene una refernecua al actor al que esta asociado el componente

	TankVanguardGameMode = Cast<ATankVanguardGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamegeTaken(
	AActor* DamagedActor, //Actor que esta siendo afectado por la accion
	float Damage, //Cantidad de damage
	const UDamageType* DamageType, //Tipo de damage, en el juego pueden variar
	AController* Instigator, //Referencia al controlador asociado con el actor que causo el damage
	AActor* DamageCauser) //Actor que causo el damage, info del origen del damage
{
	if (Damage <= 0.f) return;

	Health -= Damage;

	if (Health <= 0.f && TankVanguardGameMode)
	{
		TankVanguardGameMode->ActorDied(DamagedActor);
	}
}

float UHealthComponent::GetHealthPercent() const
{
	return Health / MaxHealt;
}

void UHealthComponent::GiveHealth(float HealthAmount)
{
	Health = Health + HealthAmount;
	UE_LOG(LogTemp, Warning, TEXT("Health given, now"));
}