#pragma once
#include "Environment.h"
class MoveEnv :
	public Environment
{
public:
	MoveEnv();
	~MoveEnv();
	void init(); 

	vector <float> pStart;
	vector <float> pOne;
	vector <float> pEnd;

	float fitnessFunction(MorphologyPointer morph);
	float updateEnv(MorphologyPointer morph);
	float lastCall(MorphologyPointer morph);
	virtual float start(MorphologyPointer morph) { return 0.0f; };


};

