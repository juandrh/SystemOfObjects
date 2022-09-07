// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
	CellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cell Mesh"));
	RootComponent = CellMesh;
	

}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
	Material = CellMesh->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACell::SavePrevious() {
    Previous = State; 
  }

void ACell::NewState(int s) {
    State = s;
	Scale = this ->GetActorScale3D();
	
	if (Previous == 1 && State == 1) { 
		Color = FVector(1.0f,1.0f,1.0f);
		Emissive= 0.0f;
		this ->SetActorScale3D(FVector(Scale.X,Scale.Y,1.4));};
	if (Previous == 0 && State == 1) {
		Color = FVector(0.8f,0.7f,0.1f);
		Emissive= 0.0f;
		this ->SetActorScale3D(FVector(Scale.X,Scale.Y,1.2));};    
    if (Previous == 1 && State == 0) {
		Color = FVector(1.0f,0.7f,0.2f);
		Emissive= 0.0f;
		this->SetActorScale3D(FVector(Scale.X,Scale.Y,1.1));};
    if (Previous == 0 && State == 0) {
		Color = FVector(0.0f,0.0f,0.0f);
		Emissive= 0.0f;
		this->SetActorScale3D(FVector(Scale.X,Scale.Y,1));};
	this->ChangeColor(Color,Emissive);
  }

  void  ACell::ChangeColor(FVector color, float emissive)
{	
	DynMaterial->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(FVector(color)));
	DynMaterial->SetScalarParameterValue(FName(TEXT("Emissive")), emissive);
	CellMesh->SetMaterial(0, DynMaterial); 	
}

 int  ACell::GetPrevious()
 {
		return Previous;
 }



 int ACell::GetState()
 {
		return State;
 }


void  ACell::SetInitState(int s)
{
 	State = s;	
    Previous = State;
	if (State == 1) {Color = FVector(1.0f,1.0f,1.0f);}
    else { Color = FVector(0.0f,0.0f,0.0f);};
	this->ChangeColor(Color,0.0f);

}