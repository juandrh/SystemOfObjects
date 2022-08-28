// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	UPROPERTY (EditAnywhere, Category = "Propiedades")
	TSubclassOf<class AAgent> AgentClass;
	UPROPERTY (EditAnywhere, Category = "Propiedades")
	FVector TargetLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Get Line Trace Hit Location"))
	void GetLineTraceHitLocation(FVector vector);

private:

	int Num_Agents = 150;

};
