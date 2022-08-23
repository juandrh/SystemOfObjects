// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalSystem.h"
#include "Engine/World.h"
#include "Unit.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Transform.h"
#include "UtilsLib.h"


// Sets default values
AGlobalSystem::AGlobalSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalSystem::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Location(0.0f, 0.0f,0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	for (int i=0; i < Num_Units; i++ ){
	GetWorld()->SpawnActor<AUnit>(UnitClass, Location, Rotation);
	}

	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Iniciado!"));

/* 	 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), UnitClass, FoundActors);
	TArray<AActor*> FoundActors;
	TArray<UActorComponent*> components;
	for (AActor* Actor : FoundActors)
	{
		
    (*Actor).SetActorLocation(Location);

	
 	 (*Actor).GetComponents(components);
	for (int32 ii = 0; ii < comector);
		}ponents.Num(); ++ii){

		//	Scale us.
		//
		USceneComponent* sc = Cast<USceneComponent>(components[ii]);
		if (sc){
			sc->SetRelativeScale3D(ScaleV

	} */
			
			
}

// Called every frame
void AGlobalSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), UnitClass, FoundActors);
	
	for (AActor* Actor : FoundActors)	
	{
		AUnit* unit = Cast<AUnit>(Actor);	
		FVector gravity = FVector(0.0, 0.0,-0.1);
		FVector wind = FVector(0.005,0.0, 0.0 );
		unit->applyForce(gravity);
		unit->applyForce(wind);		
		unit->Update(); 
	}
}

