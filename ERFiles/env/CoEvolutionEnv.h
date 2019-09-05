#pragma once
#include "MoveEnv.h"
class CoEvolutionEnv :
	public MoveEnv
{
public:
	CoEvolutionEnv();
	~CoEvolutionEnv();
	void init(); 
	float fitnessFunction(MorphologyPointer morph);
	float updateEnv(MorphologyPointer morph);
	vector<float> fitnessFunction(MorphologyPointer morph1, MorphologyPointer morph2);
	virtual float start(MorphologyPointer morph) { return 0.0f; };

};

