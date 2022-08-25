// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attractor.generated.h"


UCLASS()
class SISTEMA01_API AAttractor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttractor();
	UPROPERTY(EditDefaultsOnly, Category = "Propiedades")
	UStaticMeshComponent* AttractorMesh;	
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector realLocation;

private:

	double BodyMass;    
  	double G;       // Gravitational Constant	
  	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION (BlueprintCallable)
	FVector GetGravityForce(AUnit* unit);
	UFUNCTION (BlueprintCallable)
	double GetBodyMass();
	UFUNCTION (BlueprintCallable)
	void SetBodyMass(double mass);
	UFUNCTION (BlueprintCallable)
	FVector GetRealLocation();
	UFUNCTION (BlueprintCallable)
	void SetRealLocation(FVector realLoc);

};
