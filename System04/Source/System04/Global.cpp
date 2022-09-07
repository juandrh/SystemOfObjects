// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AGlobal::AGlobal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UClass> CellBP (TEXT("Blueprint'/Game/Blueprints/BP_Cell.BP_Cell_C'")); 
		if (CellBP.Object){
        CellClass = CellBP.Object;    
    }  
	

}

// Called when the game starts or when spawned
void AGlobal::BeginPlay()
{
	Super::BeginPlay();	
	this->CreateCells();	
}

// Called every frame
void AGlobal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!OnCreation){GenerateNext();};
}

void AGlobal::CreateCells()
{
	
	OnCreation = true;
	Board.Empty();
	FActorSpawnParameters SpawnInfo; 
	FVector InitLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator InitRotation = FRotator(0.0f, 0.0f, 0.0f);
 	for (int32 i = 0; i < Cols; i++) {       
        for (int32 j = 0; j < Cols; j++) { 		
			InitLocation = FVector( i*SceneSize/Cols,j*SceneSize/Cols,10.0f);			
			Board.Add(GetWorld()->SpawnActor<ACell>(CellClass, InitLocation, InitRotation, SpawnInfo)); 
			Cell = Cast<ACell>(Board[i*Cols + j]);				
			if(FMath::FRand()<PercentInitCells){
				Cell->SetInitState(1);
			} else {Cell->SetInitState(0);			
			};
		 }
	}
	OnCreation = false;
		 
 }

void AGlobal::GenerateNext()
{
	for ( int i = 0; i < Cols;i++) {
      for ( int j = 0; j < Cols;j++) {
		Cell = Cast<ACell>(Board[i*Cols + j]);
        Cell->SavePrevious();
      }
    }
	for (int x = 0; x < Cols; x++) {
      for (int y = 0; y < Cols; y++) {
        neighbors = 0;
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
			Cell = Cast<ACell>( Board[((x+i+Cols)%Cols)*Cols+((y+j+Cols)%Cols)]);
            neighbors += Cell->GetPrevious();
          }
        }
        Cell = Cast<ACell>(Board[x*Cols + y]);
		neighbors -= Cell->GetPrevious();

        // Rules of Life
		ActualState = Cell->GetState();
        if      ((ActualState == 1) && (neighbors <=  Loneliness)) Cell->NewState(0);           // Loneliness
        else if ((ActualState == 1) && (neighbors >=  Overpopulation)) Cell->NewState(0);           // Overpopulation
        else if ((ActualState == 0) && (neighbors == Reproduction)) Cell->NewState(1);           // Reproduction
        else {Cell->NewState(ActualState);  };	
      }
    }
}

void AGlobal::SetPercentCells(float percent)
{
	PercentInitCells = percent;
}
	
	
void AGlobal::SetLoneliness(int value)
{
	Loneliness = value;
}
	
void AGlobal::SetOverpopulation(int value)
{
	Overpopulation = value;
}
	
	
void AGlobal::SetReproduction(int value)
{
	Reproduction = value;
}