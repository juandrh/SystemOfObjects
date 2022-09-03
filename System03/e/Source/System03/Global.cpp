// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"
#include "ForceField.h"
#include "UtilsLib.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Transform.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AGlobal::AGlobal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (AgentType == 1){
	static ConstructorHelpers::FObjectFinder<UClass> AgentBP (TEXT("Blueprint'/Game/Blueprints/BP_Agent.BP_Agent_C'")); 
		if (AgentBP.Object){
        AgentClass = AgentBP.Object;    
    }  
	} else {
	static ConstructorHelpers::FObjectFinder<UClass> AgentBP (TEXT("Blueprint'/Game/Blueprints/BP_Agent2.BP_Agent2_C'")); 
		if (AgentBP.Object){
        AgentClass = AgentBP.Object;    
    }
	}
	
}

// Called when the game starts or when spawned
void AGlobal::BeginPlay()
{
	Super::BeginPlay();	
	this->CreateAgents();
}

// Called every frame
void AGlobal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	for (AActor* actor : FoundAgents)	
	{
		agent = Cast<AAgent>(actor);		
		
		agent->ApplyForce(FieldForceAmount * FField->GetCellItem(agent->GetActorLocation()));
						
		agent->ApplyForce(SeparateForceAmount*agent-> Separate(FoundAgents));
		agent->ApplyForce(AlignForceAmount*agent-> Align(FoundAgents));
		agent->ApplyForce(CohesionForceAmount*agent-> Cohesion(FoundAgents));
		if(seek){	agent->ApplyForce(15.0f*SeekForceAmount*agent->Seek(TargetLocation));  }
		if(flee){	agent->ApplyForce(FleeForceAmount*agent->Flee(TargetLocation));  }				
		agent->Update(); 		
	}	
}

// Get location of the line Trace hit in the world
// Function called by left click mouse button from Blueprint
 void AGlobal::GetLineTraceHitLocation(FVector vector, int operation)
{
	if (vector.X < BoundaryMargin) { vector.X=BoundaryMargin;};
	if (vector.X > EscenarioSize - BoundaryMargin) { vector.X=EscenarioSize - BoundaryMargin;};
	if (vector.Y < BoundaryMargin) { vector.Y=BoundaryMargin;};
	if (vector.Y > EscenarioSize - BoundaryMargin) { vector.Y=EscenarioSize - BoundaryMargin;};
	if (vector.Z < BoundaryMargin) { vector.Z=BoundaryMargin;};
	if (vector.Z > EscenarioSize/2.0f - BoundaryMargin) { vector.Z=EscenarioSize/2.0f - BoundaryMargin;};

	TargetLocation = vector;	
	if (operation == 0){ seek = true;}
	else{flee = true;}
} 

void AGlobal::DisableSeek(){
	seek = false;
	flee = false;
}

void AGlobal::SetFieldForceAmount(float ForceAmount)
{
	FieldForceAmount = ForceAmount;	  
}

void AGlobal::SetSeekForceAmount(float ForceAmount)
{
	SeekForceAmount = ForceAmount;	  
}
void AGlobal::SetFleeForceAmount(float ForceAmount)
{
	FleeForceAmount = ForceAmount;	  
}	
void AGlobal::SetSeparateForceAmount(float ForceAmount)
{
	SeparateForceAmount = ForceAmount;	  
}
void AGlobal::SetAlignForceAmount(float ForceAmount)
{
	AlignForceAmount = ForceAmount;	  
}
void AGlobal::SetCohesionForceAmount(float ForceAmount)
{
	CohesionForceAmount = ForceAmount;	  
}

void AGlobal::SetNumAgents(int num)
{
	Num_Agents = num;	  
}

void AGlobal::CreateAgents()
{
	FActorSpawnParameters SpawnInfo; 
	TArray<AAgent*> Agents;

	FVector InitLocation = FVector(EscenarioSize/2.0f-400.0f, EscenarioSize/2.0f-200.0f, EscenarioSize/2.0f-200.0f);
	FRotator InitRotation = FRotator(0.0f, 0.0f, 0.0f);
	TargetLocation = FVector(EscenarioSize/2.0f+400.0f, EscenarioSize/2.0f-200.0f, EscenarioSize/2.0f-200.0f);
	 
	for (int i=0; i < Num_Agents; i++ )
	{
	
	 InitLocation = FVector(
		(EscenarioSize-400)*FMath::FRand()+200,
		(EscenarioSize-400)*FMath::FRand()+200,
		(EscenarioSize/2.0f-400)*FMath::FRand()+200); 
	
	InitRotation = FRotator(360*FMath::FRand(), 360*FMath::FRand(),360*FMath::FRand() );
	Agents.Add(GetWorld()->SpawnActor<AAgent>(AgentClass, InitLocation, InitRotation, SpawnInfo)); 
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AgentClass, FoundAgents);
}

void AGlobal::SetSeparationDistance(float dist)
{
	for (AActor* actor : FoundAgents)	
	{
		agent = Cast<AAgent>(actor);
		agent->SetSeparationDistance(dist);
	}
}
void AGlobal::SetAlignDistance(float dist)
{
	for (AActor* actor : FoundAgents)	
	{
		agent = Cast<AAgent>(actor);
		agent->SetAlignDistance(dist);
	}
}

void AGlobal::SetCohesionDistance(float dist)
{
	for (AActor* actor : FoundAgents)	
	{
		agent = Cast<AAgent>(actor);
		agent->SetCohesionDistance(dist);
	}
}