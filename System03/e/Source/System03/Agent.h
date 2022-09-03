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
	float Pi = 3.1415926535897932384626433832795f; 
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynMaterial;		
	FVector Velocity;	
	FVector MaxVelocity = FVector(7.0f,7.0f,7.0f); 	
	FVector Acceleration = FVector(0.0f,0.0f,0.0f); 	
	FVector MaxForce = FVector(0.225f,0.225f,0.225f); 	
	double AgMass= 10.00;	
	float Speed = 6.0f;
	float Angle=0.0f;
	float Distance;
	float AmountMovementNoise ;
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
	AAgent* OtherAgent;
	float ScenarioSize = 3000.0f;
	int NumNeighbours;
	FVector SumDesiredDirection;
	float distanceBetweenAgents;
	float SeparationDistance = 50.0f;	
	float AlignDistance= 300.0f;
	float CohesionDistance= 300.0f;
	bool isCyclicalScenario = false;
	
	
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
	void AddRandomMovement();	
	void RotateBody();	
	FVector GetAgAcceleration() ;
	void Limit(FVector &vector, FVector min,FVector max);	
	void Boundaries();			
	
	void ChangeAgColor(FVector color);	

	void ApplyForce(FVector force);	
	FVector Seek(FVector target); 
	FVector Flee(FVector target); 	
	FVector Separate (TArray<AActor*> Agents);
	FVector Align (TArray<AActor*> Agents);
	FVector Cohesion (TArray<AActor*> Agents);
	void SetSeparationDistance(float dist);
	void SetAlignDistance(float dist);
	void SetCohesionDistance(float dist);

};
