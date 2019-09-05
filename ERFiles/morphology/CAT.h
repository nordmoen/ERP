#pragma once
#include "FixedBaseMorphology.h"

class CAT : public FixedBaseMorphology
{
public:
	CAT();
	~CAT();
	float fitness;
	void init_noMorph();
	virtual	void init();
	virtual void grow(int);
	void update();
	void create();


//	virtual void mutate(float mutationRate){};
	virtual	void setMainHandlePosition(float position[3]) {};
	virtual int getMainHandle();
	void saveGenome(int indNum, float fitness);
	bool loadGenome(int individualNumber, int sceneNum);
	int catHandle;
	shared_ptr<Morphology> clone() const;
	void mutate();
	vector<float> vestibularUpdate();
	vector<float> tactileUpdate();
	vector<float> proprioUpdate();
	vector<float> catInputs();
	vector<int> getObjectHandles(int parentHandle);
	vector<int> getJointHandles(int parentHandle);
	int floorHandle;
	vector <int> feet;
	vector <int> jointHandles;
	vector<int> outputHandles;
	vector<int> outputValues;

	struct VestibularAttributes {
		shared_ptr<VestibularAttributes> clone() const {
			return make_unique<VestibularAttributes>(*this);
		};
		float headPosition[3];
		float headOrientation[3];
		float errorHeadPosition[3];
		float previousHeadPosition[3];
		float headAcceleration[3];

		float headRotation[3];
		float errorHeadRotation[3];
		float headRotAcceleration[3];
		float previousHeadRotation[3]; 

		float normalizedHeadOrientation[6];
	};
	shared_ptr<VestibularAttributes> va;
};

