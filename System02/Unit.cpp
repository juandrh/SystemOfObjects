// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "Components/StaticMeshComponent.h"
#include "UtilsLib.h"
#include "GlobalSystem.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Unit Mesh"));
	RootComponent = UnitMesh;

	LocationScale = AGlobalSystem::LocationScale();
	timeScale = 1.0E+05;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	/* FVector newLocat;
	newLocat.X = UtilsLib::NormalDistGen(MaxLocation/2,MaxLocation/2);
	newLocat.Y = UtilsLib::NormalDistGen(MaxLocation/2,MaxLocation/2);
	newLocat.Z = 100.0f;
	this->SetActorLocation(newLocat);	
	FVector currentScale ;	
	massBody = UtilsLib::NormalDistGen(0.25f,0.25f);
	currentScale =this->GetActorScale3D();
	this->SetActorScale3D(currentScale * massBody * 0.10 );
	velocity = FVector(FMath::FRand()*1.0f,FMath::FRand()*1.0f,0.0f);
	acceleration = FVector(0.0f,0.0f,0.0f); */
	/* FString Msg;
	Msg = FString::Printf(TEXT("-->   %f : %f"), newLocat.X,newLocat.Y);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Msg); */

	
	acceleration = FVector(0.0f,0.0f,0.0f); 
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnit::Update()
{	
	this->SetVelocity();
	this->SetRealLocation();		
	//UE_LOG(LogTemp, Warning,TEXT("Pos->   %f : %f : %f"), realLocation.X,realLocation.Y,realLocation.Z);
	//UE_LOG(LogTemp, Warning,TEXT("Vel->   %f : %f : %f"), velocity.X,velocity.Y,velocity.Z);
	//UE_LOG(LogTemp, Warning,TEXT("acc->   %f : %f : %f"), acceleration.X,acceleration.Y,acceleration.Z);
	//UE_LOG(LogTemp, Warning,TEXT("UnrealPos->   %f : %f : %f"), realLocation.X/1.0E+08,realLocation.Y/1.0E+08,realLocation.Z/1.0E+08);
	
	this->SetUnrealLocation();
	acceleration *=0 ;
}

void AUnit::SetRealLocation()
{	
	realLocation += velocity*timeScale;	
}

FVector AUnit::GetRealLocation()
{
	return realLocation;
}	
void AUnit::SetInitRealLocation(FVector realLoc)
{	
	realLocation = realLoc;	
}

void AUnit::SetUnrealLocation()
{
	this->SetActorLocation (realLocation*LocationScale);
}

void AUnit::SetInitialVelocity(FVector vel)
{
	velocity = vel;
}

void AUnit::SetVelocity()
{
	velocity += acceleration*timeScale;
}

FVector AUnit::GetVelocity()
{
	return velocity;
}

FVector AUnit::GetAcceleration()
{
	return acceleration;
}

void AUnit::applyForce(FVector force)
{
	acceleration += force/BodyMass;
}


float AUnit::GetBodyMass()
{
	return BodyMass;
}

void AUnit::SetBodyMass(double Mass)
{
	BodyMass=Mass;
}

void AUnit::changeColor(FVector color)
{
	Material = UnitMesh->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(Material, NULL);	
	DynMaterial->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(FVector(color)));
	UnitMesh->SetMaterial(0, DynMaterial); 
}




