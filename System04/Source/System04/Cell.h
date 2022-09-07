// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

UCLASS()
class SYSTEM04_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();
	UPROPERTY(EditDefaultsOnly, Category = "Propiedades")
	UStaticMeshComponent* CellMesh;


private:
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynMaterial;
	TArray<USceneComponent*> MeshChildren;	
	int32 State;
  	int32 Previous;	
	FVector Color;
	float Emissive;
	FVector Scale;
	  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ChangeColor(FVector color,float emissive);
	void SavePrevious();
	void NewState(int s);
	int  GetPrevious();
	int GetState();
	void  SetInitState(int s);

};