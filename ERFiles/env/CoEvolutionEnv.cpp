#include "CoEvolutionEnv.h"



CoEvolutionEnv::CoEvolutionEnv()
{
}


CoEvolutionEnv::~CoEvolutionEnv()
{
}

void CoEvolutionEnv::init() {
	simLoadScene("scenes/DefaultERLight.ttt");
//	cout << "LOADING ROUGH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	initialPos.resize(3);
	initialPos[0] = 0.0;
	initialPos[1] = 0.0;
	initialPos[2] = 0.5;
	minimumHeigth = 0.3;
	timeCheck = 2.5;
	maxTime = 20.0;
//	cout << "environment Initialized" << endl;
//	simSetInt32Parameter(sim_intparam_dynamic_step_divider, 25);
	//envObjectHandles.clear();
	//float size[3] = { 1.0, 1.8, 0.02 };
	//int plate1 = simCreatePureShape(0, 24, size, 0, NULL);
	//int plate3 = simCreatePureShape(0, 24, size, 0, NULL);
	//size[0] = 1.8; size[1] = 1.0;
	//int plate2 = simCreatePureShape(0, 24, size, 0, NULL);
	//int plate4 = simCreatePureShape(0, 24, size, 0, NULL);
	//float pos[3] = { 0.7, 0.7, 0.01 };
	//simSetObjectPosition(plate1, -1, pos);
	//pos[0] = -0.7;
	//simSetObjectPosition(plate2, -1, pos);
	//pos[1] = -0.7;
	//simSetObjectPosition(plate3, -1, pos);
	//pos[0] = 0.7;
	//simSetObjectPosition(plate4, -1, pos);
	//envObjectHandles.push_back(plate1);
	//envObjectHandles.push_back(plate2);
	//envObjectHandles.push_back(plate3);
	//envObjectHandles.push_back(plate4);
}

float CoEvolutionEnv::fitnessFunction(MorphologyPointer morph) {
	float fitness = 0;
	//if (morph->modular == false) {
	//	cout << "getting main handle" << endl;
	//	int mainHandle = morph->getMainHandle();
	//	float pos[3];
	//	simGetObjectPosition(mainHandle, -1, pos);
	//	fitness = sqrtf(pos[0] * pos[0]) + sqrtf(pos[1] * pos[1]);
	//	//	fitness = 0; // no fixed morphology that can absorb light
	//}
	//else {
	//	int mainHandle = morph->getMainHandle();
	//	float pos[3];
	//	simGetObjectPosition(mainHandle, -1, pos);
	//	fitness = sqrtf(pos[0] * pos[0]) + sqrtf(pos[1] * pos[1]) + sqrtf(pos[2] * pos[2]);

	//	//	vector<shared_ptr<ER_Module> > createdModules = morph->getCreatedModules();
	//	//	vector<float> pos = createdModules[0]->getPosition();
	//	//	fitness = sqrtf(pos[0] * pos[0]) + sqrtf(pos[1] * pos[1]);
	//}
    fitness = MoveEnv::fitnessFunction(morph);
	return fitness;
}

float CoEvolutionEnv::updateEnv(MorphologyPointer morph) {
	MoveEnv::updateEnv(morph);
	return 0;
}

vector<float> CoEvolutionEnv::fitnessFunction(MorphologyPointer morph1, MorphologyPointer morph2)
{
	int br1 = morph1->getAmountBrokenModules();
	int br2 = morph2->getAmountBrokenModules();
	int cm1 = morph1->createdModules.size();
	int cm2 = morph2->createdModules.size();
	float fit1 = 0.0;
	float fit2 = 0.0;
	if (br1 < 1) {
		fit2 = 0.0;
	}
	else {
		fit2 = (br1 / cm1) - br2;
	}
	if (br2 < 1) {
		fit1 = 0.0;
	}
	else {
		fit1 = (br2 / cm2) - br1;
	}
	float pos1[3];
	simGetObjectPosition(morph1->getMainHandle(), morph2->getMainHandle(), pos1);
	float adder = sqrt(pow(pos1[0],2) * pow(pos1[1],2));
	fit1 -= adder;
	fit2 -= adder;
	vector<float> fitnesses;
	fitnesses.push_back(fit1);
	fitnesses.push_back(fit2);
	return fitnesses;
}
