// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalSystem.h"
#include "Engine/World.h"
#include "Unit.h"
#include "Attractor.h"
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

	double SunScaling =5.0E-10; 
	double TerrestrialPlanetScaling =1.0; 
	double GasGiantScaling = 2.5e+02;
	double LocationScale = this->LocationScale();
	double SizeScale = 3.0E-06;

	FVector Location;
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	
	FActorSpawnParameters SpawnInfo; 
	TArray<AUnit*> Planets;

	// Sun	
	Location=FVector(1.81899E+08, 9.83630E+08,-1.58778E+07);	
	AAttractor* Sun = GetWorld()->SpawnActor<AAttractor>(AttractorClass, Location*LocationScale, Rotation, SpawnInfo); 
	Sun->SetRealLocation(Location);
	Sun->SetActorScale3D(6.95500E+08*FVector(1.0, 1.0,1.0)*SunScaling);
	Sun->SetBodyMass(1.98854E+30);

	// Mercury
	Location=FVector(-5.67576E+10, -2.73592E+10,2.89173E+09);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 	
	Planets[0]->SetInitRealLocation(Location);
	Planets[0]->SetBodyMass(3.30200E+23);
	Planets[0]->SetActorScale3D(2.44000E+06*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[0]->SetInitialVelocity(FVector(11660.9474,-41486.84876,-4459.788723));
	Planets[0]->changeColor(FVector(0.358333,0.1559,0.011654));

	// Venus
	Location=FVector(4.28480E+10, 1.00073E+11,-1.11872E+09);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[1]->SetInitRealLocation(Location);
	Planets[1]->SetBodyMass(4.86850E+24);
	Planets[1]->SetActorScale3D(6.05180E+06*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[1]->SetInitialVelocity(FVector(-32281.7526,	13688.45124,2050.641277));
	Planets[1]->changeColor(FVector(0.135561,1.0,0.0));

	// Earth
	Location=FVector(-1.43778E+11, -4.00067E+10,-1.38875E+07);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[2]->SetInitRealLocation(Location);
	Planets[2]->SetBodyMass(5.97219E+24);
	Planets[2]->SetActorScale3D(6.37101E+06*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[2]->SetInitialVelocity(FVector(7662.7574,-28758.94876,1.814817));
	Planets[2]->changeColor(FVector(0.10,0.82507,1.0));

	// Mars
	Location=FVector(-1.14746E+11, -1.96294E+11,-1.32908E+09);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[3]->SetInitRealLocation(Location);
	Planets[3]->SetBodyMass(6.41850E+23);
	Planets[3]->SetActorScale3D(3.38990E+06*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[3]->SetInitialVelocity(FVector(21848.1474,-10120.74876,-748.225723));
	Planets[3]->changeColor(FVector(1.0,0.153619,0.0));

	//  Jupiter
	Location=FVector(-5.66899E+11, -5.77495E+11,1.50755E+10);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[4]->SetInitRealLocation(Location);
	Planets[4]->SetBodyMass(1.89813E+27);
	Planets[4]->SetActorScale3D(6.99110E+07*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[4]->SetInitialVelocity(FVector(9179.1774,-8539.98876,-170.035723));
	Planets[4]->changeColor(FVector(0.5625,0.5625,0.5625));

	//  Saturn
	Location=FVector(8.20513E+10, -1.50241E+12, 2.28565E+10);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[5]->SetInitRealLocation(Location);
	Planets[5]->SetBodyMass(5.68319E+26);
	Planets[5]->SetActorScale3D(5.82320E+07*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[5]->SetInitialVelocity(FVector(9124.3674,488.82324,-371.911723));
	Planets[5]->changeColor(FVector(0.425,0.425,0.425));

	//  Uranus
	Location=FVector(2.62506E+12, 1.40273E+12, -2.87982E+10);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[6]->SetInitRealLocation(Location);
	Planets[6]->SetBodyMass(8.68103E+25);
	Planets[6]->SetActorScale3D(2.53620E+07*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[6]->SetInitialVelocity(FVector(-3248.1226,5681.23124,62.988177));
	Planets[6]->changeColor(FVector(0.225,0.61565,0.61565));

	//  Neptune
	Location=FVector(4.30300E+12, -1.24223E+12, -7.35857E+10);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[7]->SetInitRealLocation(Location);
	Planets[7]->SetBodyMass(1.02410E+26);
	Planets[7]->SetActorScale3D(2.46240E+07*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[7]->SetInitialVelocity(FVector(1482.5674,5246.08124,-142.969723));
	Planets[7]->changeColor(FVector(0.002514,0.000484,1));

	//  Pluto
	Location=FVector(1.65554E+12, -4.73503E+12, 2.77962E+10);	
	Planets.Add(GetWorld()->SpawnActor<AUnit>(UnitClass, Location*LocationScale, Rotation, SpawnInfo)); 
	Planets[8]->SetInitRealLocation(Location);
	Planets[8]->SetBodyMass(1.30700E+22);
	Planets[8]->SetActorScale3D(1.19500E+06*FVector(1.0, 1.0,1.0)*TerrestrialPlanetScaling*SizeScale);
	Planets[8]->SetInitialVelocity(FVector(5256.6574,630.96124,-1607.358723));
	Planets[8]->changeColor(FVector(0.9625,0.9625,0.9625));

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

	TArray<AActor*> FoundAttractors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AttractorClass, FoundAttractors);
	
	for (AActor* Attractor : FoundAttractors)
	{
		AAttractor* attractor = Cast<AAttractor>(Attractor);

		for (AActor* Actor : FoundActors)	
		{
			AUnit* unit = Cast<AUnit>(Actor);
			FVector gravity = attractor->GetGravityForce(unit);

		 	/* FString Msg;
			Msg = FString::Printf(TEXT("-->   %f :%f :%f :"), gravity.X,gravity.Y,gravity.Z);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Msg);   */

			unit->applyForce(gravity);				
			unit->Update(); 
		}
	}
}

double AGlobalSystem::LocationScale()
{
   return 2.50E-09;
}

