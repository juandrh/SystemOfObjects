// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"
#include "UtilsLib.h"
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
	AgentMesh->GetChildrenComponents(false,MeshChildren);	
	AgMass = AgMass + FMath::FRand() * 50.0f;
	MaxVelocity = (MaxVelocity * Speed );
	
	//float scale = FMath::FRand()*1.2+0.3;
	//this->SetActorScale3D(FVector(scale,scale,scale));

	if (AgentType == 1){
		TArray<USceneComponent*> MeshChildrens;
		AgentMesh->GetChildrenComponents(false,MeshChildrens);
		Angle = (float)MeshChildren[0]->GetComponentRotation().Roll;
		AmountMovementNoise = FMath::FRand()* 6.0f + 1.0f;
	} else {Angle = 0;}

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
	
	AgentMesh->GetChildrenComponents(false,MeshChildren);	
	if (AgentType == 1){ 
		// MeshChildren:   1 -> Head 
		Velocity2D =Velocity * FVector(1.0f,1.0f,0.0f);		
		Angle += Velocity2D.Size(); 		
		MeshRotator = 	FRotator (
			Velocity.Rotation().Pitch,
			Velocity.Rotation().Yaw-65.0f,
			Angle);
				
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

	} else {
		MeshRotator = FRotator (0.0f, Velocity.Rotation().Yaw,5.0f);	
		MeshChildren[0]->SetWorldRotation(FMath::RInterpTo(
				MeshChildren[0]->GetComponentRotation(),
				MeshRotator,
				UGameplayStatics::GetWorldDeltaSeconds(this),
				15.0f)		
		); 

	}

	
}	

void AAgent::SetAgLocation()
{	
	FVector Location = this->GetActorLocation();
	Location += Velocity;	

	if (Location.X <50.0f){Location.X = 50.0f;}
	if (Location.Y <50.0f){Location.Y = 50.0f;}
	if (Location.X > ScenarioSize-50.0f){Location.X = ScenarioSize-50.0f;}
	if (Location.Y > ScenarioSize-50.0f){Location.Y = ScenarioSize-50.0f;}

	this->SetActorLocation(Location);

	/* LocationHistory.Add(Location);
	if (LocationHistory.Num()>500){
		LocationHistory.RemoveAt(0);
	} */
}

void AAgent::SetInitialVelocity(FVector vel)
{	
	Velocity = vel;
}

void AAgent::SetAgVelocity()
{
	Velocity += Acceleration;
	Limit(Velocity, MaxVelocity * (-1),MaxVelocity);
}

FVector AAgent::GetAgVelocity()
{
	return Velocity;
}

void AAgent::AutoMove()
{
	Position = this->GetActorLocation();
	PerpendicularVeloc = FVector(Velocity.Y,-Velocity.X, 0.0f);
	PerpendicularVeloc.GetSafeNormal();
	Noise = FMath::PerlinNoise3D(Position/20)*AmountMovementNoise;  	
	ApplyForce(PerpendicularVeloc * Noise);
}

FVector AAgent::GetAgAcceleration()
{
	return Acceleration;
}

void AAgent::ApplyForce(FVector force)
{
	Acceleration += force/AgMass;
	Limit(Acceleration, FVector(0.0f,0.0f,0.0f),MaxForce);  
}

void AAgent::ChangeAgColor(FVector color)
{
	Material = AgentMesh->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(Material, NULL);	
	DynMaterial->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(FVector(color)));
	AgentMesh->SetMaterial(0, DynMaterial); 
}

 void AAgent::Seek(FVector target) {
    DesiredDirection = target -  this->GetActorLocation();

	if  (DesiredDirection.Size()<200.0f){
		float dist = DesiredDirection.Size();
		DesiredDirection.Normalize();		
    	DesiredDirection *= MaxVelocity*(dist/200.0f);
		} else {
		DesiredDirection.Normalize();		
    	DesiredDirection *= MaxVelocity;
	}

    Steer = DesiredDirection - Velocity;	 
	Limit(Steer, MaxForce *(-1.0f),MaxForce);    
    this->ApplyForce(Steer);
  }

void AAgent::Flee(FVector target) {
    DesiredDirection = target -  this->GetActorLocation();

	if  (DesiredDirection.Size()<200.0f){
		float dist = DesiredDirection.Size();
		DesiredDirection.Normalize();		
    	DesiredDirection *= MaxVelocity*(dist/200.0f);
		} else {
		DesiredDirection.Normalize();		
    	DesiredDirection *= MaxVelocity;
	}

    Steer = DesiredDirection - Velocity;
	Steer *= (-1.5f);	 
	Limit(Steer, MaxForce *(-1.0f),MaxForce);    
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
 
   void AAgent::Boundaries(float EscenarioSize,float BoudaryMargin) {

    DesiredDirection = FVector(0.0f,0.0f,0.0f);
	Position = this->GetActorLocation();

    if (Position.X < BoudaryMargin) {
      DesiredDirection = FVector(MaxVelocity.X, Velocity.Y, 0.0f);
    } 
    else if (Position.X > EscenarioSize -BoudaryMargin) {
      DesiredDirection = FVector(-MaxVelocity.X, Velocity.Y, 0.0f);
    } 

    if (Position.Y < BoudaryMargin) {
      DesiredDirection = FVector( Velocity.X,MaxVelocity.Y, 0.0f);
    } 
    else if (Position.Y > EscenarioSize-BoudaryMargin) {
      DesiredDirection = FVector(Velocity.X,-MaxVelocity.Y, 0.0f);
    } 

    
      DesiredDirection.Normalize();
      DesiredDirection*= MaxVelocity;
      Steer =DesiredDirection -Velocity;
	  Limit(Steer, MaxForce*(-1.0f),MaxForce);         
      this->ApplyForce(Steer);
    
  }  
