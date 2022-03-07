// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "G_Spaceship_Eli.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class UPawnMovementComponent;
class UFloatingPawnMovement;
class AG_Planet;

UCLASS()
class GRAVITY_API AG_Spaceship_Eli : public APawn
{
	GENERATED_BODY()

protected:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpaceshipMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* SpaceshipPawnMovementComponent;



protected:
	//variables
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bIsDebugging;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool bIsBeingAffectedByGravity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ShipRotatingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ShipFowardSpeed;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float CurrentRotationRate;

	AG_Planet* CurrentPlanetToRotateReference;

protected:

	void MoveFoward(float AxisValue);

	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Test(AG_Planet* PlanetToRotate, float DeltaTime);

public:
	// Sets default values for this pawn's properties
	AG_Spaceship_Eli();

	UFUNCTION(BlueprintCallable)
	void SetIsBeingAffectedByGravity(bool NewState) { bIsBeingAffectedByGravity = NewState; };

	UFUNCTION(BlueprintCallable)
	void SetCurrentPlanetReference(AG_Planet* NewPlanetReference) { CurrentPlanetToRotateReference = NewPlanetReference; };

	void RotateAroundPlanet(AG_Planet* PlanetToRotate, float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
