// Fill out your copyright notice in the Description page of Project Settings.


#include "Attractor.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AAttractor::AAttractor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AttractorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Attractor Mesh"));
	RootComponent = AttractorMesh;
	
    G = 6.67e-11;  //Gravitational constant
}

// Called when the game starts or when spawned
void AAttractor::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AAttractor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AAttractor::GetGravityForce(AUnit* unit)
{	
	FVector force = (this->GetRealLocation())-((*unit).GetRealLocation());   // force's direction 
    double distance = force.Size();                        // distance between unit and attractor               
    force.Normalize();                             
	double gravForceMag = (G * BodyMass * (*unit).GetBodyMass()) / (distance * distance);    
    force *= gravForceMag;    
	//UE_LOG(LogTemp, Warning,TEXT("f->   %f : %f : %f"), force.X,force.Y,force.Z);
    return force;	
}

double AAttractor::GetBodyMass()
{
	return BodyMass;
}

void AAttractor::SetBodyMass(double mass)
{
	BodyMass=mass;
}

FVector AAttractor::GetRealLocation()
{
	return realLocation;
}	

void AAttractor::SetRealLocation(FVector realLoc)
{
	realLocation = realLoc;
}

