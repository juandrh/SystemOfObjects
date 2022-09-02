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
	
	// Random mass, initial velocity and initial rotation
	AgMass = AgMass + FMath::FRand() * 50.0f;	
	Velocity = FVector(FMath::FRand()*2.0f-1.0f,FMath::FRand()*2.0f-1.0f,0.0f)*5.0f;
	AgentMesh->GetChildrenComponents(false,MeshChildren);	
	if (AgentType == 1){
		TArray<USceneComponent*> MeshChildrens;
		AgentMesh->GetChildrenComponents(false,MeshChildrens);
		Angle = (float)MeshChildren[0]->GetComponentRotation().Roll;
		AmountMovementNoise = FMath::FRand()* 3.0f + 1.0f;
	} else {Angle = 0;}
	Material = AgentMesh->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	this->ChangeAgColor(FVector(FMath::FRand(),FMath::FRand(),0.0));
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAgent::Update()
{		
	this->SetAgVelocity();
	this->AddRandomMovement();  
	this->SetAgLocation();	
	this->RotateBody();		
	Acceleration *=0 ;
	//UE_LOG(LogTemp, Warning,TEXT("V->   %f : %f - %f : %f "), Velocity.X,Velocity.Y,Acceleration.X,Acceleration.Y);    
}

	

void AAgent::SetAgLocation()
{	
	FVector Location = this->GetActorLocation();	
	Location += Velocity;
	Position = Location;	
	if (!isCyclicalScenario){
	Limit(Location,FVector(50.0f,50.0f,55.0f),FVector(ScenarioSize-50.0f,ScenarioSize-50.0f,55.0f));
	} else {
		if (Location.X<= 50.0f){ Position.X = ScenarioSize-51.0f;}
		if (Location.X>= ScenarioSize-50.0f){ Position.X = 51.0f;}
		if (Location.Y<= 50.0f){ Position.Y = ScenarioSize-51.0f;}
		if (Location.Y>= ScenarioSize-50.0f){ Position.Y = 51.0f;}

	}
	this->SetActorLocation(Position);
	/* LocationHistory.Add(Location);
	if (LocationHistory.Num()>500){
		LocationHistory.RemoveAt(0);
	} */
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
		 MeshRotator = FRotator (0.0f, Velocity.Rotation().Yaw,0.0f);	
		this->SetActorRotation(MeshRotator)	;			
	}	
}
void AAgent::SetInitialVelocity(FVector vel)
{	
	Velocity = vel;
}

void AAgent::SetAgVelocity()
{
	
	Velocity += Acceleration;
	Limit(Velocity, MaxVelocity * (-1),MaxVelocity);
	Boundaries();
}

FVector AAgent::GetAgVelocity()
{
	return Velocity;
}

void AAgent::AddRandomMovement()
{
	Position = this->GetActorLocation();
	PerpendicularVeloc = FVector(Velocity.Y,-Velocity.X, 0.0f);
	PerpendicularVeloc.GetSafeNormal();	
	Noise = FMath::PerlinNoise3D(Position/20)*AmountMovementNoise;  	
	ApplyForce(PerpendicularVeloc* Noise);
}

FVector AAgent::GetAgAcceleration()
{
	return Acceleration;
}

void AAgent::ApplyForce(FVector force)
{
	Acceleration += force/AgMass;
	Limit(Acceleration, MaxForce*(-1.0f),MaxForce);  
}



 
// Aux funtion to limit Fvector between min and max
void AAgent::Limit(FVector &vector, FVector min,FVector max)
{
	if (vector.X < min.X) { vector.X=min.X;};
	if (vector.X > max.X) { vector.X=max.X;};
	if (vector.Y < min.Y) { vector.Y=min.Y;};
	if (vector.Y > max.Y) { vector.Y=max.Y;};
	if (vector.Z < min.Z) { vector.Z=min.Z;};
	if (vector.Z > max.Z) { vector.Z=max.Z;};
}
 
 	// Set behaviour in scene boundaries
void AAgent::Boundaries()
{
	if (!isCyclicalScenario){
		Position = this->GetActorLocation();
		if (Position.X <= 50.f || Position.X >= ScenarioSize -50.0f ) {
			Velocity.X= -Velocity.X; 	   
		} else if (Position.Y <= 50.f || Position.Y >= ScenarioSize -50.0f ) {
			Velocity.Y= -Velocity.Y;
		} 
	}
   
}  

FVector AAgent::Seek(FVector target) 
{
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
    return Steer;
}

FVector AAgent::Flee(FVector target)
{
    DesiredDirection = this->GetActorLocation()-target ;

	if  (DesiredDirection.Size()<200.0f){
		float dist = DesiredDirection.Size();
		DesiredDirection.Normalize();		
    	DesiredDirection *= MaxVelocity*(dist/200.0f);
		} else {
		DesiredDirection.Normalize();		
    	DesiredDirection *= MaxVelocity;
	}

    Steer = DesiredDirection - Velocity;			    
    return Steer;
}

FVector AAgent::Separate (TArray<AActor*> Agents)
{    
    SumDesiredDirection = FVector(0.0f,0.0f,0.0f) ;
    NumNeighbours = 0;
   
    for (AActor* actor : Agents)	{
			OtherAgent = Cast<AAgent>(actor);
			DesiredDirection = this->GetActorLocation() - OtherAgent->GetActorLocation() ;
			DesiredDirection.Z = 0.0f;
			distanceBetweenAgents = DesiredDirection.Size();
			
			if ((distanceBetweenAgents > 0) && (distanceBetweenAgents < SeparationDistance)) {	
				DesiredDirection.Normalize();
				DesiredDirection /= distanceBetweenAgents;        
				SumDesiredDirection += DesiredDirection;
				NumNeighbours++;     
			}      
    }

    if (NumNeighbours > 0) {  
      SumDesiredDirection /= NumNeighbours; 
	  SumDesiredDirection.Normalize();
	  SumDesiredDirection *= Speed * 1.5f;
      Steer = SumDesiredDirection - Velocity; 	  		    	  
      return Steer;
	  
    }

	return FVector(0.0f,0.0f,0.0f) ;
}


FVector AAgent::Align (TArray<AActor*> Agents) {
	
   SumDesiredDirection = FVector(0.0f,0.0f,0.0f) ;
    NumNeighbours = 0;
   
    for (AActor* actor : Agents)	{
			OtherAgent = Cast<AAgent>(actor);
			DesiredDirection = this->GetActorLocation() - OtherAgent->GetActorLocation() ;
			DesiredDirection.Z = 0.0f;
			distanceBetweenAgents = DesiredDirection.Size();
			
			if ((distanceBetweenAgents > 0) && (distanceBetweenAgents < AlignDistance)) {	
				 
				SumDesiredDirection += DesiredDirection;
				NumNeighbours++;     
			}      
    }

    if (NumNeighbours > 0) {  
      SumDesiredDirection /= NumNeighbours; 
	  SumDesiredDirection.Normalize();
	  SumDesiredDirection *= Speed * 1.5f;
      Steer = SumDesiredDirection - Velocity;	  	  		    	  
      return Steer;
	  
    } 

	return FVector(0.0f,0.0f,0.0f) ;
}

FVector AAgent::Cohesion (TArray<AActor*> Agents)
{
	 SumDesiredDirection = FVector(0.0f,0.0f,0.0f) ;
    NumNeighbours = 0;   
    for (AActor* actor : Agents)	{
			OtherAgent = Cast<AAgent>(actor);
			DesiredDirection = this->GetActorLocation() - OtherAgent->GetActorLocation() ;
			DesiredDirection.Z = 0.0f;
			distanceBetweenAgents = DesiredDirection.Size();
			
			if ((distanceBetweenAgents > 0) && (distanceBetweenAgents < CohesionDistance)) {	
				 
				SumDesiredDirection += OtherAgent->GetActorLocation();
				NumNeighbours++;     
			}      
    }

    if (NumNeighbours > 0) {  
      SumDesiredDirection /= NumNeighbours; 	  	  		    	  
      return Seek(SumDesiredDirection)*0.01f;	  
    } 
 
	return FVector(0.0f,0.0f,0.0f) ;
}

void AAgent::ChangeAgColor(FVector color)
{
	
	
	Material = AgentMesh->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(Material, NULL);	
	DynMaterial->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(FVector(color)));
	AgentMesh->SetMaterial(0, DynMaterial); 
	
}

void AAgent::SetSeparationDistance(float dist)
{
	SeparationDistance = dist;
}
void AAgent::SetAlignDistance(float dist)
{
	AlignDistance = dist;
}

void AAgent::SetCohesionDistance(float dist)
{
	CohesionDistance = dist;
}