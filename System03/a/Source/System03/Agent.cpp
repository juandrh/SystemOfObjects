// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Math/UnrealMathVectorCommon.h"


// Sets default values
AAgent::AAgent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Agent Mesh"));
	RootComponent = AgentMesh;

}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	TArray<USceneComponent*> MeshChildren;
	AgentMesh->GetChildrenComponents(false,MeshChildren);	
	AgMass = AgMass + FMath::FRand() * 50.0f;
	MaxVelocity = (MaxVelocity * Speed );
	//MaxVelocity = (MaxVelocity * Speed *(FMath::FRand() ) / 2 )+ FVector(Speed/2.0f,Speed/2.0f,0.0f);
	//float scale = FMath::FRand()*1.2+0.3;
	//this->SetActorScale3D(FVector(scale,scale,scale));

	TArray<USceneComponent*> MeshChildrens;
	AgentMesh->GetChildrenComponents(false,MeshChildrens);
	angle = (float)MeshChildren[0]->GetComponentRotation().Roll;

}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAgent::Update()
{	
		
	this->SetAgVelocity();
	this->SetAgLocation();	
	this->RotateBody();
	
	Acceleration *=0 ;
}

void AAgent::RotateBody()
{
	TArray<USceneComponent*> MeshChildren;
	AgentMesh->GetChildrenComponents(false,MeshChildren);
	FRotator MeshRotator;

	FVector path =Velocity * FVector(1.0f,1.0f,0.0f);
	
	
	//UE_LOG(LogTemp, Warning,TEXT("a->   %f : %f : %f"),(float)MeshChildren[0]->GetComponentRotation().Roll,angle );

	angle += path.Size(); 
	
	MeshRotator = 	FRotator (
		Velocity.Rotation().Pitch,
		Velocity.Rotation().Yaw-65.0f,
		angle);
			
	MeshChildren[0]->SetWorldRotation(
		FMath::RInterpTo(
			MeshChildren[0]->GetComponentRotation(),
			MeshRotator,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			3.5f)		
		); 
	
	// MeshChildren:   1 -> Head 
	MeshRotator = FRotator (0.0f, Velocity.Rotation().Yaw,5.0f);	
	MeshChildren[1]->SetWorldRotation(FMath::RInterpTo(
			MeshChildren[1]->GetComponentRotation(),
			MeshRotator,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			15.0f)		
		); 
	
}	

void AAgent::SetAgLocation()
{	
	FVector Location = this->GetActorLocation();
	Location += Velocity;
	this->SetActorLocation(Location);	
}


void AAgent::SetInitLocation(FVector Loc)
{	
	this->SetActorLocation(Loc);	
}


void AAgent::SetInitialVelocity(FVector vel)
{
	
	
	Velocity = vel;
}

void AAgent::SetAgVelocity()
{
	Velocity += Acceleration;
	Limit(Velocity, FVector(0.0f,0.0f,0.0f),MaxVelocity);
}

FVector AAgent::GetAgVelocity()
{
	return Velocity;
}

FVector AAgent::GetAgAcceleration()
{
	return Acceleration;
}

void AAgent::ApplyForce(FVector force)
{
	Acceleration += force/AgMass;
}

void AAgent::ChangeAgColor(FVector color)
{
	Material = AgentMesh->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(Material, NULL);	
	DynMaterial->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(FVector(color)));
	AgentMesh->SetMaterial(0, DynMaterial); 
}

 void AAgent::Seek(FVector target) {
    FVector desired = target -  this->GetActorLocation();

	if  (desired.Size()<200.0f){
		float dist = desired.Size();
		desired.Normalize();		
    	desired *= MaxVelocity*(dist/200.0f);
		} else {
		desired.Normalize();		
    	desired *= MaxVelocity;
	}

    FVector Steer = desired - Velocity;	     
    this->ApplyForce(Steer);
  }

  void AAgent::Limit(FVector vector, FVector min,FVector max)
  {
	if (vector.X < min.X) { vector.X=min.X;};
	if (vector.X > max.X) { vector.X=max.X;};
	if (vector.Y < min.Y) { vector.Y=min.Y;};
	if (vector.Y > max.Y) { vector.Y=max.Y;};
	if (vector.Z < min.Z) { vector.Z=min.Z;};
	if (vector.Z > max.Z) { vector.Z=max.Z;};
  }
 
