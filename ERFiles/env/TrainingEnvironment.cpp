#include "TrainingEnvironment.h"



TrainingEnvironment::TrainingEnvironment()
{
}


TrainingEnvironment::~TrainingEnvironment()
{
}

void TrainingEnvironment::init() {
	simLoadScene("scenes/trainingEnvironment.ttt");
	initialPos.resize(3);
	initialPos[0] = 0.0;
	initialPos[1] = 0.0;
	initialPos[2] = 0.5;
	minimumHeigth = 0.3;
	timeCheck = 2.5;
	maxTime = 20.0;
	
	// loop through object tree
	int baseHandle = simGetObjectHandle("training_env");
	simAddObjectToSelection(sim_handle_tree, baseHandle);
	int shapesStorage[50]; // stores up to 20 shapes
	simGetObjectSelection(shapesStorage);
	forceSensorHandles.clear();
	for (int i = 0; i < 50; i++) {
		int objectType = simGetObjectType(shapesStorage[i]);
		if (objectType == sim_object_forcesensor_type) {
			forceSensorHandles.push_back(shapesStorage[i]);
		}
	}
	simRemoveObjectFromSelection(sim_handle_all, -1);
}

float TrainingEnvironment::fitnessFunction(MorphologyPointer morph)
{
	float fitness = 0;
	int mainHandle = morph->getMainHandle();
	float pos[3];
	simGetObjectPosition(mainHandle, -1, pos);
	pEnd.push_back(pos[0]);
	pEnd.push_back(pos[1]);

	if (pOne.size() < 1) {
		//			cout << "Note, pOne never set" << endl;
		fitness += -(pEnd[0]);
	}
	else {
		fitness += -(pEnd[0] - pOne[0]);
	}
	pOne.clear();
	pEnd.clear();
	return fitness + brokenParts;
}

float TrainingEnvironment::lastCall(MorphologyPointer morph) {
	brokenParts = 0;
	// loop through object tree
	int baseHandle = simGetObjectHandle("training_env");
	simAddObjectToSelection(sim_handle_tree, baseHandle);
	int shapesStorage[50]; // stores up to 20 shapes
	simGetObjectSelection(shapesStorage);
	forceSensorHandles.clear();
	for (int i = 0; i < 50; i++) {
		int objectType = simGetObjectType(shapesStorage[i]);
		if (objectType == sim_object_forcesensor_type) {
			forceSensorHandles.push_back(shapesStorage[i]);
		}
	}
	simRemoveObjectFromSelection(sim_handle_all, -1);

	for (int i = 0; i < forceSensorHandles.size(); i++) {
		int force = simReadForceSensor(forceSensorHandles[i], NULL, NULL);
		float pos[3];
		simGetObjectPosition(forceSensorHandles[i], -1, pos);
		//cout << pos[0] << pos[1] << pos[2] << endl;
		//cout << force << endl;
		if (force != 0 && force != -1) {
			if (force == 3) {
				//cout << "Cube " << i << " is broken" << endl;
				brokenParts += 1;
			}
		}
	}


	return brokenParts;
}

float TrainingEnvironment::updateEnv(MorphologyPointer morph) {
	MoveEnv::updateEnv(morph);
	return 0;
}