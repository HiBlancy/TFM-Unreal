// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable.h"
#include "GameFramework/Actor.h"
#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APickable::APickable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	RootComponent = PickupMesh;

	PickupBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Pickup Box"));
	PickupBox->SetupAttachment(PickupMesh);
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickable::OnPlayerEnterPickupBox);
}

void APickable::BeginPlay()
{
	Super::BeginPlay();
}

void APickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickable::OnPlayerEnterPickupBox(
	UPrimitiveComponent* OverlapedComp, //componente primitivo que detecto la colision
	AActor* OtherActor, //actor quien a entrado en el area de colision
	UPrimitiveComponent* OtherComp, //componente del actor que hizo la colision
	int32 OtherBodyIndex, //en nuestro caso es el 0, ya que ese es el default de nuestro jugador
	bool bFromSweep, //indica si la colision resulto ser un sweep
	const FHitResult& SweepResult) //info del impacto
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		Destroy();
	}

	if (PickupSound) //Sonido diferente con cada pickup, por eso esta en el padre
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			PickupSound,
			GetActorLocation());
	}
}