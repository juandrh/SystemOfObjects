// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Agent.h"
#include "FlowField.h"
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
	//UPROPERTY (EditAnywhere, Category = "Propiedades")
	TSubclassOf<class AAgent> AgentClass;
	UPROPERTY (EditAnywhere, Category = "Propiedades")
	FVector TargetLocation;
	float EscenarioSize = 8000.0f;
	float BoudaryMargin = 200.0f;
	float FieldIntesitive = 8.0f;
	int AgentType = 1;
	bool seek = false;
	
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Get Line Trace Hit Location"))
	void GetLineTraceHitLocation(FVector vector);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Disable Seek"))
	void DisableSeek();

private:

	int Num_Agents = 100;
	FlowField FField;

};
