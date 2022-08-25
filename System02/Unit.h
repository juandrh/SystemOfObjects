// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

UCLASS()
class SISTEMA01_API AUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();
	UPROPERTY(EditDefaultsOnly, Category = "Propiedades")
	UStaticMeshComponent* UnitMesh;	
	UPROPERTY(EditDefaultsOnly, Category = "Propiedades")
	double LocationScale;
	UPROPERTY(EditDefaultsOnly, Category = "Propiedades")
	double timeScale;

private:
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector realLocation;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector velocity;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector acceleration;	
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	double BodyMass;
	UMaterialInstanceDynamic* DynMaterial;


	


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION (BlueprintCallable)
	void Update();
	UFUNCTION (BlueprintCallable)
	void SetRealLocation();
	UFUNCTION (BlueprintCallable)
	void SetInitRealLocation(FVector realLoc);
	UFUNCTION (BlueprintCallable)
	void SetInitialVelocity(FVector vel);
	void SetVelocity();
	FVector GetVelocity();	
	FVector GetAcceleration() ;
	UFUNCTION (BlueprintCallable)
	float GetBodyMass();
	UFUNCTION (BlueprintCallable)
	void SetBodyMass(double Mass);
	UFUNCTION (BlueprintCallable)
	void applyForce(FVector force);
	UFUNCTION (BlueprintCallable)
	void changeColor(FVector color);
	UFUNCTION (BlueprintCallable)
	FVector GetRealLocation();
	UFUNCTION (BlueprintCallable)
	void SetUnrealLocation();
	
	

};
