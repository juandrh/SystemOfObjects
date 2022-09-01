
#pragma once

#include "CoreMinimal.h"

/**
 *   
 */
class SYSTEM03_API UtilsLib

{
public:
	UtilsLib();
	~UtilsLib();


	static float NormalDistGen(float mu,float sigma);	
	static float Noise();
	
};
