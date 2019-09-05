#pragma once
#include "MoveEnv.h"
class TrainingEnvironment :
	public MoveEnv
{
public:
	TrainingEnvironment();
	~TrainingEnvironment();
	void init(); 
	float fitnessFunction(MorphologyPointer morph);
	float updateEnv(MorphologyPointer morph);
	float lastCall(MorphologyPointer morph);
	float brokenParts = 0.0;
	vector<int> forceSensorHandles;
	virtual float start(MorphologyPointer morph) { return 0.0f; };

};

