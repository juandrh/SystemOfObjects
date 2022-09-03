// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Agent.h"
#include "ForceField.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global.generated.h"

UCLASS()
class SYSTEM03_API AGlobal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobal(); 

private:
	//UPROPERTY(EditAnywhere, Category = "Propiedades")
	TSubclassOf<class AAgent> AgentClass;	
	FVector TargetLocation;
	float EscenarioSize = 3000.0f;
	float BoundaryMargin = 50.0f;	
	int AgentType = 2;  // Type 1 or 2 , change in Agent.h too.
	bool seek = false;
	bool flee = false;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	int Num_Agents = 200;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	AForceField* FField;
	TArray<AActor*> FoundAgents;
	AAgent* agent;	
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float FieldForceAmount = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float SeekForceAmount = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float FleeForceAmount = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float SeparateForceAmount = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float AlignForceAmount = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float CohesionForceAmount = 0.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Get Line Trace Hit Location"))
	void GetLineTraceHitLocation(FVector vector, int operation);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Disable Seek"))
	void DisableSeek();
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Field Force Amount"))
	void SetFieldForceAmount(float ForceAmount);
		UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Seek Force Amount"))
	void SetSeekForceAmount(float ForceAmount);
		UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Flee Force Amount"))
	void SetFleeForceAmount(float ForceAmount);
		UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Separate Force Amount"))
	void SetSeparateForceAmount(float ForceAmount);
		UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Align Force Amount"))
	void SetAlignForceAmount(float ForceAmount);
		UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Cohesion Force Amount"))
	void SetCohesionForceAmount(float ForceAmount);
			UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Number agents"))
	void SetNumAgents(int num);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Create agents"))
	void CreateAgents();
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Separation Distance"))
	void SetSeparationDistance(float dist);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Align Distance"))
	void SetAlignDistance(float dist);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Cohesion Distance"))
	void SetCohesionDistance(float dist);



};
