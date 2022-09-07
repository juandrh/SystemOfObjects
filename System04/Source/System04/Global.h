// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cell.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global.generated.h"

UCLASS()
class SYSTEM04_API AGlobal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobal();
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Create Cells"))
	void CreateCells();	
	void GenerateNext();

private:
	float SceneSize =2800.0f;
	int Cols = 140;  	
	TSubclassOf<class ACell> CellClass;
	ACell* Cell;	
	TArray<AActor*>  Board;
	int32 ActualState = 0;
	int neighbors;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	bool OnCreation = true;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	float PercentInitCells = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	int Loneliness = 1;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	int Reproduction = 3;
	UPROPERTY(EditAnywhere, Category = "Propiedades")
	int Overpopulation = 4;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector GetCellItem(FVector position);	
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Percent Cells"))
	void SetPercentCells(float percent);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Loneliness"))
	void SetLoneliness(int value);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Reproduction"))
	void SetReproduction(int value);
	UFUNCTION (BlueprintCallable,meta = (DisplayName = "Set Overpopulation"))
	void SetOverpopulation(int value);


};
