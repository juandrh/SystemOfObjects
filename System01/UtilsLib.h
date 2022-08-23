// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SISTEMA01_API UtilsLib
{
public:
	UtilsLib();
	~UtilsLib();


	static float NormalDistGen(float mu,float sigma);	
	static float Noise();
};
