// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"
#include "Agent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Transform.h"
#include "UtilsLib.h"

// Sets default values
AGlobal::AGlobal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobal::BeginPlay()
{
	Super::BeginPlay();


	FVector InitLocation = FVector(0.0f, 200.0f, 50.0f);
	FRotator InitRotation = FRotator(0.0f, 0.0f, 0.0f);
	TargetLocation = FVector(0.0f, 200.0f, 0.0f);
	
	FActorSpawnParameters SpawnInfo; 
	TArray<AAgent*> Agents;
 
	for (int i=0; i < Num_Agents; i++ )
	{
	InitLocation = FVector(50.0f+6000*FMath::FRand()-3000, 50.0f + 6000*FMath::FRand()-3000, 50.0f);
	
	InitRotation = FRotator(0.0f, 180*FMath::FRand(),0.0f );
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


		agent->Seek(TargetLocation);
		agent->Update(); 
		
	}

}


// Get location of the line Trace hit in the world
// Function called by left click mouse button from Blueprint
 void AGlobal::GetLineTraceHitLocation(FVector vector)
{
 	/* FString Msg;
	Msg = FString::Printf(TEXT("Position: %f , %f , %f"),vector.X,vector.Y,vector.Z);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Msg);  */

	TargetLocation = vector;	
} 