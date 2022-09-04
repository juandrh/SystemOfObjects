// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Arrow.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForceField.generated.h"

UCLASS()
class SYSTEM03_API AForceField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForceField();
	UPROPERTY(EditDefaultsOnly, Category = "Propiedades")
	UStaticMeshComponent* ArrowMesh;	
	

private:
	TArray<FVector> field;
  	int cols = 50;  	
	float Pi = 3.1415926535897932384626433832795f; 
	TSubclassOf<class AArrow> ArrowClass;	
	TArray<AActor*> FoundArrows;
	AArrow* Arrow;
	FVector ArrowDireection;
	TArray<USceneComponent*> MeshChildren;
	bool ShowField = false;
	float EscenarioSize = 6000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector GetCellItem(FVector position);



};
