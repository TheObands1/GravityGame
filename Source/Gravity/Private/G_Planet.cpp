// Fill out your copyright notice in the Description page of Project Settings.


#include "G_Planet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "G_Spaceship_Eli.h"

// Sets default values
AG_Planet::AG_Planet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlanetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
	RootComponent = PlanetMesh;


	GravitationalScope = CreateDefaultSubobject<USphereComponent>(TEXT("GravitationalScope"));
	GravitationalScope->SetupAttachment(RootComponent);
	GravitationalScope->SetSphereRadius(900);

	GravityRadius = 450;//GravitationalScope->GetUnscaledSphereRadius();
	RotationSpeed = 50;

}

// Called when the game starts or when spawned
void AG_Planet::BeginPlay()
{
	Super::BeginPlay();

	GravitationalScope->OnComponentBeginOverlap.AddDynamic(this, &AG_Planet::BeginRotateObjectAroundPlanet);
	GravitationalScope->OnComponentEndOverlap.AddDynamic(this, &AG_Planet::EndRotateObjectAroundPlanet);
	
}

void AG_Planet::BeginRotateObjectAroundPlanet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReduceGravityRadius, this, &AG_Planet::ReduceGravityRadius, 1.0f, true);
		AG_Spaceship_Eli* PossibleSpaceship = Cast<AG_Spaceship_Eli>(OtherActor);
		if(IsValid(PossibleSpaceship))
		{
			PossibleSpaceship->SetIsBeingAffectedByGravity(true);
			PossibleSpaceship->SetCurrentPlanetReference(this);
		}

		
	}
}

void AG_Planet::EndRotateObjectAroundPlanet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		AG_Spaceship_Eli* PossibleSpaceship = Cast<AG_Spaceship_Eli>(OtherActor);
		if (IsValid(PossibleSpaceship))
		{
			PossibleSpaceship->SetIsBeingAffectedByGravity(false);
			PossibleSpaceship->SetCurrentPlanetReference(nullptr);
			
		}
		else
		{
			//Create a rotating actor class if I want to do more with it
		}

	}

	//SOLUCION CADA QUIEN MANEJA SU ROTACION PARA QUE PUEDAN HABER MULTIPLES COSAS ROTANDO
}

void AG_Planet::ReduceGravityRadius()
{
	if (GravityRadius <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReduceGravityRadius);
	}
	else
	{
		GravityRadius -= GravitationalPullRate;
	}
}

// Called every frame
void AG_Planet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

