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


public:


	//variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool bIsBeingAffectedByGravity;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ShipRotatingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ShipFowardSpeed;


protected:

	void MoveFoward(float AxisValue);

	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Test(float AxisValue);

public:
	// Sets default values for this pawn's properties
	AG_Spaceship_Eli();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
