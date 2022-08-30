// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"
#include "FlowField.h"
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

	FField = FlowField ();

	FVector InitLocation = FVector(EscenarioSize/2-400.0f, EscenarioSize/2-200.0f, 50.0f);
	FRotator InitRotation = FRotator(0.0f, 0.0f, 0.0f);
	TargetLocation = FVector(EscenarioSize/2+400.0f, EscenarioSize/2-200.0f, 50.0f);
	
	FActorSpawnParameters SpawnInfo; 
	TArray<AAgent*> Agents;
 
	for (int i=0; i < Num_Agents; i++ )
	{
	
	 InitLocation = FVector(
		(EscenarioSize-1000)*FMath::FRand()+500,
		(EscenarioSize-1000)*FMath::FRand()+500,
		50.0f); 
	
	InitRotation = FRotator(0.0f, 360*FMath::FRand(),0.0f );
	Agents.Add(GetWorld()->SpawnActor<AAgent>(AgentClass, InitLocation, InitRotation, SpawnInfo)); 

	

	}


}

// Called every frame
void AGlobal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> FoundAgents;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AgentClass, FoundAgents);
	
	for (AActor* actor : FoundAgents)	
	{
		AAgent* agent = Cast<AAgent>(actor);

		
		agent->ApplyForce(FieldIntesitive * FField.GetCellItem(agent->GetActorLocation()));
		//UE_LOG(LogTemp, Warning,TEXT("t->   %f : %f "), TargetLocation.X,TargetLocation.Y);
		agent-> AutoMove();	

		if(seek){	agent->Seek(TargetLocation);  }

		agent->Boundaries(EscenarioSize,BoudaryMargin);
		agent->Update(); 

		
		agent->RotateBody();
		
	}

}


// Get location of the line Trace hit in the world
// Function called by left click mouse button from Blueprint
 void AGlobal::GetLineTraceHitLocation(FVector vector)
{
	if (vector.X < BoudaryMargin) { vector.X=BoudaryMargin;};
	if (vector.X > EscenarioSize - BoudaryMargin) { vector.X=EscenarioSize - BoudaryMargin;};
	if (vector.Y < BoudaryMargin) { vector.Y=BoudaryMargin;};
	if (vector.Y > EscenarioSize - BoudaryMargin) { vector.Y=EscenarioSize - BoudaryMargin;};
	
	TargetLocation = vector;	
	seek = true;

} 

void AGlobal::DisableSeek(){

	seek = false;

}