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

private:
	//UPROPERTY(EditAnywhere, Category = "Propiedades")
	TSubclassOf<class AAgent> AgentClass;	
	FVector TargetLocation;
	float EscenarioSize = 6000.0f;
	float BoudaryMargin = 200.0f;
	float FieldIntesitive = 8.0f;
	int AgentType = 2;  // Type 1 or 2 , change in Agent.h too.
	bool seek = false;
	bool flee = false;
	int Num_Agents = 1200;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	AForceField* FField;
	TArray<AActor*> FoundAgents;
	AAgent* agent;

};
