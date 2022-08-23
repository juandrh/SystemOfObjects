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

private:
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector velocity;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector acceleration;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float MaxVelocity = 4;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float MaxAcceleration = 4;	
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float massBody;
	UMaterialInstanceDynamic* DynMaterial;

	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float MaxLocation = 1500;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION (BlueprintCallable)
	void Update();
	void SetUnitLocation();	
	void SetVelocity();
	FVector GetVelocity();
	void SetAcceleration(FVector newVelocity);
	FVector GetAcceleration() ;
	UFUNCTION (BlueprintCallable)
	float GetMassBody();
	UFUNCTION (BlueprintCallable)
	void applyForce(FVector force);
	void changeColor(FVector color);
	UFUNCTION (BlueprintCallable)
	void changeEmissive();
	

};
