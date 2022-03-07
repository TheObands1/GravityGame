// Fill out your copyright notice in the Description page of Project Settings.


#include "G_Spaceship_Eli.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Math/UnrealMathUtility.h"
#include "G_Planet.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"


// Sets default values
AG_Spaceship_Eli::AG_Spaceship_Eli()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpaceshipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceshipMesh"));
	RootComponent = SpaceshipMesh;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	//SpringArmComponent->SetUsingAbsoluteRotation(true); //So that is does not rotate when ship does
	SpringArmComponent->TargetArmLength = 1200.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-80.0f, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false; //Don't want to pull in camera when it collides with something

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	//SpringArmComponent->bUsePawnControlRotation = false; //Camera does not rotate relative to arm

	SpaceshipPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("SpaceshipPawnMovementComponent"));

	bIsBeingAffectedByGravity = false;
	ShipRotatingSpeed = 10;
	ShipFowardSpeed = 0.5;
	CurrentRotationRate = 0.0f;

}

// Called when the game starts or when spawned
void AG_Spaceship_Eli::BeginPlay()
{
	Super::BeginPlay();
}

void AG_Spaceship_Eli::MoveFoward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AG_Spaceship_Eli::MoveRight(float AxisValue)
{

	AddControllerYawInput(AxisValue);
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), GetControlRotation(), GetWorld()->GetDeltaSeconds(), ShipRotatingSpeed);
	SetActorRotation(NewRotation);
	//AddMovementInput(GetActorRightVector() * AxisValue);
	//AddControllerYawInput(GetActorRotation().Yaw * AxisValue);
	//BP_Test(AxisValue);
}

// Called every frame
void AG_Spaceship_Eli::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsBeingAffectedByGravity)
	{
		//MoveFoward(ShipFowardSpeed);
	}
	else
	{
		if (IsValid(CurrentPlanetToRotateReference))
		{
			SpaceshipPawnMovementComponent->StopMovementImmediately();
			RotateAroundPlanet(CurrentPlanetToRotateReference, DeltaTime);
		}
	}
	
}

void AG_Spaceship_Eli::RotateAroundPlanet(AG_Planet* PlanetToRotate, float DeltaTime)
{
	bIsBeingAffectedByGravity = true;
	BP_Test(PlanetToRotate, DeltaTime);

	/*
	CurrentRotationRate += DeltaTime*PlanetToRotate->GetRotationSpeed();
	FVector VectorToRotate = FVector(PlanetToRotate->GetGravityRadius(), 0, 0);

	FVector NewPosition = UKismetMathLibrary::RotateAngleAxis(VectorToRotate, (PlanetToRotate->GetAngleOfRotation() * CurrentRotationRate), FVector(0, 0, 1));

	FVector FinalPosition = GetActorLocation() + NewPosition;

	this->SetActorLocation(FinalPosition

	//PROBLEMA IDENTIFICADO: La posición de la nave al empezar a girar DEPENDE del ángulo inicial que yo le ponga al planeta
	//CORRECCIÓN QUE DEBO HACER: Calcular ese angúlo dependiendo de donde la nave entra 

	*/

	if (bIsDebugging)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), PlanetToRotate->GetActorLocation(), FColor::Cyan, false, 1.0f, 1.0f, 1.0f);
	}
}

// Called to bind functionality to input
void AG_Spaceship_Eli::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AG_Spaceship_Eli::MoveRight);

	PlayerInputComponent->BindAxis("MoveFoward", this, &AG_Spaceship_Eli::MoveFoward);

}

