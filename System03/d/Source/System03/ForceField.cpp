// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "ForceField.h"
#include "Arrow.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AForceField::AForceField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	float xoff = FMath::FRand();
    for (int i = 0; i < cols; i++) {
        float yoff = FMath::FRand();
        for (int j = 0; j < cols; j++) { 
            float noise = (FMath::PerlinNoise2D(FVector2D(xoff,yoff))+1.0f)*2.0* Pi; // mapping  0 - 2Pi
            field.Add(FVector(FMath::Cos(noise),FMath::Sin(noise),0.0f));			
            yoff += 0.03f;
            }
        xoff += 0.03f;
    }   

    static ConstructorHelpers::FObjectFinder<UClass> ArrowBP (TEXT("Blueprint'/Game/blueprints/BP_Arrow.BP_Arrow_C'")); 
		if (ArrowBP.Object){
        ArrowClass = ArrowBP.Object; }



}

// Called when the game starts or when spawned
void AForceField::BeginPlay()
{
	Super::BeginPlay();
	
	if (ShowField){
		FActorSpawnParameters SpawnInfo; 
		TArray<AArrow*> Arrows;	
		FVector InitLocation; 
		FRotator InitRotation;
		FVector arrowDirection;	
		for (int i = 0; i < cols; i++) {       
			for (int j = 0; j < cols; j++) { 
				InitLocation = FVector(i*EscenarioSize/cols,j*EscenarioSize/cols,0.0f);
				arrowDirection = this->GetCellItem(InitLocation);
				InitRotation = FRotator(0.0f,0.0f,0.0f); 
				// 
				Arrows.Add(GetWorld()->SpawnActor<AArrow>(ArrowClass, InitLocation, InitRotation, SpawnInfo));
				float angle = FMath::Acos(arrowDirection.X/arrowDirection.Size());
				Arrow = Arrows.Last();
				Arrow -> Rotate(arrowDirection);
			}
		} 
	}
	
}

// Called every frame
void AForceField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AForceField::GetCellItem(FVector position)
{
   
    int i = (int)(position.X*cols/EscenarioSize);
    int j = (int)(position.Y*cols/EscenarioSize);  
	
    if (i<0 || i >cols-1 || j<0 || j >cols-1 ){
        return FVector(0.0f,0.0f,0.0f);
    } 
    return field[i*cols + j];
}
