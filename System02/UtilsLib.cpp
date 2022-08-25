// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilsLib.h"
#include <random>
#include <cmath>
#include "Math/UnrealMathUtility.h"

UtilsLib::UtilsLib()
{
}

UtilsLib::~UtilsLib()
{
}


float UtilsLib::Noise()
{
	return FMath::PerlinNoise1D(FMath::FRand());
}





float UtilsLib::NormalDistGen(float mu,float sigma ) {
/*    // return a normally distributed random value
   float v1=( (float)(FMath::FRand()) + 1. )/( (float)(RAND_MAX) + 1. );
   float v2=( (float)(FMath::FRand()) + 1. )/( (float)(RAND_MAX) + 1. );
   return cos(2*3.14*v2)*sqrt(-2.*log(v1)); */

std::random_device rd{};
std::mt19937 gen{ rd() };
std::normal_distribution<float> d{ mu, sigma };
return d(gen); 

}

