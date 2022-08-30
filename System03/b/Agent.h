// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Agent.generated.h"

UCLASS()
class SYSTEM03_API AAgent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgent();
	UPROPERTY(EditDefaultsOnly, Category = "Propiedades")
	UStaticMeshComponent* AgentMesh;	

private:
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	UMaterialInterface* Material;	
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector Velocity;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector MaxVelocity = FVector(1.0f,1.0f,0.0f); 
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector Acceleration = FVector(0.0f,0.0f,0.0f); 	
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	FVector MaxForce = FVector(0.25f,0.25f,0.0f); 
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	double AgMass= 10.00;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	UMaterialInstanceDynamic* DynMaterial;
	float Pi = 3.1415926535897932384626433832795f; 
	float Speed = 16.0f;
	float Angle=0.0f;
	float Distance;
	float AmountMovementNoise = 4.0;
	TArray<FVector> LocationHistory;
	int AgentType = 1;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION (BlueprintCallable)
	void Update();
	UFUNCTION (BlueprintCallable)
	void SetAgLocation();
	UFUNCTION (BlueprintCallable)
	void SetInitLocation(FVector realLoc);
	UFUNCTION (BlueprintCallable)
	void SetInitialVelocity(FVector vel);
	UFUNCTION (BlueprintCallable)
	void SetAgVelocity();
	UFUNCTION (BlueprintCallable)
	FVector GetAgVelocity();
	UFUNCTION (BlueprintCallable)
	void AutoMove();	
	UFUNCTION (BlueprintCallable)
	void RotateBody();
	UFUNCTION (BlueprintCallable)
	FVector GetAgAcceleration() ;	
	UFUNCTION (BlueprintCallable)
	void ApplyForce(FVector force);
	UFUNCTION (BlueprintCallable)
	void ChangeAgColor(FVector color);
	UFUNCTION (BlueprintCallable)
	void Seek(FVector target); 
	
	UFUNCTION (BlueprintCallable)
	void Limit(FVector vector, FVector min,FVector max);
	UFUNCTION (BlueprintCallable)
	void Boundaries(float EscenarioSize,float BoudaryMargin);


};
