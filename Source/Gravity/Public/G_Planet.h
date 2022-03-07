// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G_Planet.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class GRAVITY_API AG_Planet : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlanetMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* GravitationalScope;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bIsRotatingRight;

	FTimerHandle TimerHandle_ReduceGravityRadius;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta =(ClampMin = 0.0f))
	float GravityRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float AngleOfRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings",  meta = (ClampMin = 0.0f))
	float RotationRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings",  meta = (ClampMin = 0.0f))
	float RotationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings",  meta = (ClampMin = 0.0f))
	float GravitationalPullRate;
	
public:	
	// Sets default values for this actor's properties
	AG_Planet();

	float GetGravityRadius() { return GravityRadius; };

	float GetAngleOfRotation() { return AngleOfRotation; };

	float GetRotationRate() { return RotationRate; };

	float GetRotationSpeed() { return RotationSpeed; };

	float GetGravitationalPullRate() { return GravitationalPullRate; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginRotateObjectAroundPlanet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndRotateObjectAroundPlanet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ReduceGravityRadius();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
