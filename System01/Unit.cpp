// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "Components/StaticMeshComponent.h"
#include "UtilsLib.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Unit Mesh"));
	RootComponent = UnitMesh;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	FVector newLocat;
	newLocat.X = UtilsLib::NormalDistGen(MaxLocation/2,MaxLocation/2);
	newLocat.Y = UtilsLib::NormalDistGen(MaxLocation/2,MaxLocation/2);
	newLocat.Z = UtilsLib::NormalDistGen(MaxLocation/2,MaxLocation/2)+500.0;
	this->SetActorLocation(newLocat);	
	FVector currentScale ;	
	massBody = UtilsLib::NormalDistGen(1.0f,1.0f);
	currentScale =this->GetActorScale3D();
	this->SetActorScale3D(currentScale * massBody * 0.10 );
	velocity = FVector(0.0f,0.0f,0.0f);
	acceleration = FVector(0.0f,0.0f,0.0f);
	/* FString Msg;
	Msg = FString::Printf(TEXT("-->   %f : %f"), newLocat.X,newLocat.Y);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Msg); */

	Material = UnitMesh->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	this->changeColor(FVector(FMath::FRand(),FMath::FRand(),0.0));


}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnit::Update()
{	
	this->SetVelocity();
	this->SetUnitLocation();	
	acceleration *=0 ;
}

void AUnit::SetUnitLocation()
{
	FVector location = this->GetActorLocation(); 
	FVector newLocation = location + velocity;

	if (newLocation.X < -MaxLocation*2) {newLocation.X=-MaxLocation*2;velocity.X *= -1;};
	if (newLocation.Y < -MaxLocation*2) {newLocation.Y=-MaxLocation*2;velocity.Y *= -1;};
	if (newLocation.Z < 0) {newLocation.Z=0;velocity.Z *= -1;};
	if (newLocation.X > MaxLocation*2) {newLocation.X=MaxLocation*2;velocity.X *= -1;};
	if (newLocation.Y > MaxLocation*2) {newLocation.Y=MaxLocation*2;velocity.Y *= -1;};
	if (newLocation.Z > MaxLocation*10) {newLocation.Z=MaxLocation*10;velocity.Z *= -1;};

	this->SetActorLocation ( newLocation);
}

void AUnit::SetVelocity()
{
	velocity += acceleration;
}

FVector AUnit::GetVelocity()
{
	return velocity;
}

void AUnit::SetAcceleration(FVector newAcceleration)
{	
		acceleration+= newAcceleration;
}

FVector AUnit::GetAcceleration()
{
	return acceleration;
}

void AUnit::applyForce(FVector force)
{
	acceleration += force/massBody;
}


float AUnit::GetMassBody()
{
	return massBody;
}

void AUnit::changeColor(FVector color)
{
	DynMaterial->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(FVector(color)));
	UnitMesh->SetMaterial(0, DynMaterial); 
}

void AUnit::changeEmissive()
{
	FVector location = this->GetActorLocation(); 
	float emissive;
	emissive= location.Z/(MaxLocation*10);	
	DynMaterial->SetScalarParameterValue("Emissive", emissive);
	UnitMesh->SetMaterial(0, DynMaterial); 
}