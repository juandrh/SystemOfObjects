// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
	RootComponent = ArrowMesh;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	ArrowMesh->GetChildrenComponents(false,MeshChildren);	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AArrow::Rotate(FVector direction){	
	MeshRotator = 	FRotator (0.0f,	direction.Rotation().Yaw-90.0f,	0.0f);
	ArrowMesh->GetChildrenComponents(false,MeshChildren);	
	MeshChildren[0]->AddWorldRotation(MeshRotator);	
}

