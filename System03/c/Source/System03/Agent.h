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
	//UPROPERTY(EditAnywhere, Category = "Propiedades")
	UMaterialInterface* Material;		
	FVector Velocity;	
	FVector MaxVelocity = FVector(1.0f,1.0f,0.0f); 	
	FVector Acceleration = FVector(0.0f,0.0f,0.0f); 	
	FVector MaxForce = FVector(0.25f,0.25f,0.0f); 	
	double AgMass= 10.00;	
	UMaterialInstanceDynamic* DynMaterial;
	float Pi = 3.1415926535897932384626433832795f; 
	float Speed = 16.0f;
	float Angle=0.0f;
	float Distance;
	float AmountMovementNoise = 4.0;
	TArray<FVector> LocationHistory;
	int AgentType = 2; // Type 1 or 2 , change in Global.h too.
	TArray<USceneComponent*> MeshChildren;
	FRotator MeshRotator;
	FVector Velocity2D;
	FVector Position;
	FVector PerpendicularVeloc;
	float Noise;
	FVector DesiredDirection;
	FVector Steer;
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION (BlueprintCallable)	
	void Update();	
	void SetAgLocation();		
	void SetInitialVelocity(FVector vel);	
	void SetAgVelocity();	
	FVector GetAgVelocity();	
	void AutoMove();	
	void RotateBody();	
	FVector GetAgAcceleration() ;		
	void ApplyForce(FVector force);	
	void ChangeAgColor(FVector color);	
	void Seek(FVector target); 
	void Flee(FVector target); 
	void Limit(FVector vector, FVector min,FVector max);	
	void Boundaries(float EscenarioSize,float BoudaryMargin);
	float ScenarioSize = 6000.0f;



};
