// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	SmokeParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Particles"));
	SmokeParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	//AddDynamics es un controlador de eventos dinamico al evento OnComponentHit, y cuando este se activa llama al metodo de la clase asignada	
	
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			LaunchSound,
			GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComp, //Componente primitivo en el que ocurrio la colision, asociado al actor que tiene esta funcion
	AActor* OtherActor, //Actor con el que se ha producido la colision, actor involucrado en la colision
	UPrimitiveComponent* OtherComponent, //Componente primitivo del actor colisionado, componente de colision asociado al OtherActor
	FVector NormalImpulse, //Impulso normal generado por la colision, fuerza aplicada a los objetos en la direccion perpendicular a la superficie
	const FHitResult& Hit) //Info detallada de la colision (ubi, normal de la superficie en el punto de impacto...)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) 
	{
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor, //Actor que recibira el damage
			Damage, //Cantidad de damage
			MyOwnerInstigator, //Quien causa el damage
			this, //Actor que esta llamando a la funcion, indica que ese actor que esta causando el damage
			DamageTypeClass); //Tipo de damage

		if(HitParticles) //Comprobar que sea valido antes de lanzar la llamada
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				HitParticles,
				GetActorLocation(),
				GetActorRotation());
		}		

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				GetActorLocation());
		}

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}	
	
	Destroy();
}