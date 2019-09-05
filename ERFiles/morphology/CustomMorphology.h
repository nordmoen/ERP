#pragma once
#include "FixedBaseMorphology.h"
#include <math.h>

class CustomMorphology : public FixedBaseMorphology
{
public:
	CustomMorphology();
	~CustomMorphology();
	virtual vector<int> getObjectHandles(int parentHandle);
	virtual vector<int> getJointHandles(int parentHandle);
	void update();
	virtual int getMainHandle();
	void create();

	void mutate();

	void saveGenome(int indNum, float fitness);

	void init();
	shared_ptr<Morphology> clone() const;
	string name;

	vector<int> sensorHandles;
	vector<int> outputHandles;
	vector<int> outputValues;

};

