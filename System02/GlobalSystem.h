// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalSystem.generated.h"

UCLASS()
class SISTEMA01_API AGlobalSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobalSystem();

	UPROPERTY (EditAnywhere, Category = "Propiedades")
	TSubclassOf<class AUnit> UnitClass;
	UPROPERTY (EditAnywhere, Category = "Propiedades")
	TSubclassOf<class AAttractor> AttractorClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	static double LocationScale();

private:

	int Num_Units = 7;

};
