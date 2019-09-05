#pragma once
#include <vector>
#include <iostream>
#include "v_repLib.h"
#include <memory>
#include "../DefaultGenome.h"
#include "../module/ER_Module.h"
#include <cmath>

using namespace std; 

class Environment
{
public:
	Environment();
	~Environment();
	virtual void init() = 0;
	Settings* settings;
	RandNum* randNum;
	typedef shared_ptr<Morphology> MorphologyPointer;
	
	virtual float fitnessFunction(MorphologyPointer morph) = 0;
	virtual float updateEnv(MorphologyPointer morph) = 0;
	virtual float lastCall(MorphologyPointer morph) = 0;
	virtual float start(MorphologyPointer morph) = 0;


	vector<int> envObjectHandles;
	vector<float> initialPos; 
	virtual vector<float> fitnessFunction(MorphologyPointer morph1, MorphologyPointer morph2);

	float minimumHeigth = 0.0;
	float timeCheck = 0.0;
	float maxTime = 10.0; 
	void print(); 
	void sceneLoader();
	int type = 0;
protected:
};

