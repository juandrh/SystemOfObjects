// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FlowField 
{

public:
	FlowField();	
	~FlowField();
	FVector GetCellItem(FVector position);

private:
	TArray<FVector> field;
  	int cols = 500;  	
	float Pi = 3.1415926535897932384626433832795f; 
};
