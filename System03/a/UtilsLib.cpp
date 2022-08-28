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





float UtilsLib::NormalDistGen(float mu,float sigma )
{
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::normal_distribution<float> d{ mu, sigma };
    return d(gen); 

}
