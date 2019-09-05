#pragma once
#include "Environment.h"
class WaterEnv :
	public Environment
{
public:
	WaterEnv();
	~WaterEnv();
	void init(); 
	float fitnessFunction(MorphologyPointer morph);
	float updateEnv(MorphologyPointer morph);
	float lastCall(MorphologyPointer morph) { return 0.0f; };
	virtual float start(MorphologyPointer morph) { return 0.0f; };


};

