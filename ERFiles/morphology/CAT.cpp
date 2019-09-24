#include "CAT.h"
#include "v_repLib.h"
#include <iostream>
#include <fstream>

using namespace std;

CAT::CAT()
{
	float position[3] = { 0.0, 0.0, 1.0 };
	va = shared_ptr<VestibularAttributes>(new VestibularAttributes);
}


CAT::~CAT()
{
//	cout << "delete CAT class" << endl; 
}

shared_ptr<Morphology> CAT::clone() const {
	// shared_ptr<Morphology>()
	shared_ptr<CAT> cat = make_unique<CAT>(*this);
//	cat->va = va->clone();
	cat->control = control->clone();
	return cat;
}

void CAT::init_noMorph() {
	unique_ptr<ControlFactory> controlFactory(new ControlFactory);
	control = controlFactory->createNewControlGenome(0, settings, randomNum); // ann
	controlFactory.reset();
//	control->init(1, 1, 1);//morph->morph_jointHandles);
}

void CAT::init(){
	//create();
	unique_ptr<ControlFactory> controlFactory(new ControlFactory);
	control = controlFactory->createNewControlGenome(0, settings,  randomNum); // ann
	controlFactory.reset();
	control->init(50, 28, 28);
	control->mutate(0.5);
}

void CAT::grow(int i) {
	cout << "Cat cannot grow; therefore, the call to grow(int) will be dismissed." << endl;
}

void CAT::saveGenome(int indNum, float fitness) {
	cout << "saving Cat Genome " << endl << "-------------------------------- " << endl;
	ofstream genomeFile;
	ostringstream genomeFileName;
	genomeFileName << settings->repository << "/genomes" << settings->sceneNum << "/genome" << indNum << ".csv";
	//	genomeFileName << indNum << ".csv";
	genomeFile.open(genomeFileName.str());
	if (!genomeFile) {
		std::cerr << "Error opening file \"" << genomeFileName.str() << "\" to save genome." << std::endl;
	}
	genomeFile << ",#GenomeType,CatGenome," << endl;
	genomeFile << "#Individual:" << indNum << endl;
	genomeFile << "#Fitness:," << fitness << endl;
	genomeFile << "#ControlParams:," << endl;
	genomeFile << "	#ControlType,0," << endl;
	if (control) {
		genomeFile << control->getControlParams().str() << endl;
	}
	genomeFile << "#EndControlParams" << endl;
	genomeFile << "end of cat" << endl;
	cout << "saved cat" << endl;
	genomeFile.close();
}

bool CAT::loadGenome(int individualNumber, int sceneNum) {
	cout << "loading cat genome " << individualNumber << endl;
	unique_ptr<ControlFactory> controlFactory(new ControlFactory);
	control = controlFactory->createNewControlGenome(0, settings, randomNum); // ann
	controlFactory.reset();
	ostringstream genomeFileName;
	genomeFileName << settings->repository + "/genomes" << sceneNum << "/genome" << individualNumber << ".csv";
	ifstream genomeFile(genomeFileName.str());
	if (!genomeFile) {
		std::cerr << "Could not load " << genomeFileName.str() << std::endl;
		return false;
		//		std::exit(1);
	}
	string value;
	list<string> values;
	while (genomeFile.good()) {
		getline(genomeFile, value, ',');
	//	cout << value << ",";
		if (value.find('\n') != string::npos) {
			split_line(value, "\n", values);
		}
		else {
			values.push_back(value);
		}
	}
	vector<string> controlValues;
	bool checkingControl = false;

	list<string>::const_iterator it = values.begin();
	for (it = values.begin(); it != values.end(); it++) {
		string tmp = *it;
		if (checkingControl == true) {
			controlValues.push_back(tmp);
		}
		if (tmp == "#Fitness:") {
			it++;
			tmp = *it;
			fitness = atof(tmp.c_str());
		}
		if (tmp == "#ControlParams:") {
			checkingControl = true;
		}
		if (tmp == "#EndControlParams") {
			//cout << "setting control params" << endl;
			control->setControlParams(controlValues);
			controlValues.clear();
			checkingControl = false;
		}
	}
	return true;
}

void CAT::mutate() {
	if (control) {
		control->mutate(settings->mutationRate);
	}
}

vector<float> CAT::vestibularUpdate() {
	vector<float> nnInput;
	simGetObjectOrientation(mainHandle, -1, va->headOrientation);
	simGetObjectPosition(mainHandle, -1, va->headPosition);

	for (int i = 0; i < 3; i++) {
		va->errorHeadPosition[i] = va->headPosition[i] - va->previousHeadPosition[i];
		va->headAcceleration[i] = va->errorHeadPosition[i] / simGetSimulationTimeStep();
	}
	for (int i = 0; i < 3; i++) {
		va->previousHeadPosition[i] = va->headPosition[i];
	}
	for (int i = 0; i < 3; i++) {
		nnInput.push_back(va->headAcceleration[i] * 0.1);
		nnInput.push_back(va->headAcceleration[i] * -0.1);
	}

	for (int i = 0; i < 3; i++) {
		va->errorHeadRotation[i] = va->headRotation[i] - va->previousHeadRotation[i];
		va->headRotAcceleration[i] = va->errorHeadRotation[i];
	}
	for (int i = 0; i < 3; i++) {
		va->previousHeadRotation[i] = va->headRotation[i];
	}
	for (int i = 0; i < 3; i++) {
		nnInput.push_back(va->headRotAcceleration[i] * 0.1);
		nnInput.push_back(va->headRotAcceleration[i] * -0.1);
	}

	va->normalizedHeadOrientation[0] = va->headOrientation[0]; //x
	va->normalizedHeadOrientation[1] = -va->headOrientation[0]; //x 
	va->normalizedHeadOrientation[2] = va->headOrientation[1]; //y
	va->normalizedHeadOrientation[3] = -va->headOrientation[1]; //y
	va->normalizedHeadOrientation[4] = va->headOrientation[2]; //z
	va->normalizedHeadOrientation[5] = -va->headOrientation[2]; //z
	for (int i = 0; i < 6; i++) {
		nnInput.push_back(va->normalizedHeadOrientation[i]);
	}
	return nnInput;
}

vector<float> CAT::tactileUpdate() {
	vector<float> nnInput;
	for (int i = 0; i < feet.size(); i++) {
		bool collisionI = simCheckCollision(floorHandle, feet[i]);
		nnInput.push_back(collisionI);
	}
	return nnInput;
}

vector<float> CAT::proprioUpdate() {
	vector<float> nnInput;
	for (int i = 0; i < outputHandles.size(); i++) {
		float jointPos[3];
		simGetJointPosition(outputHandles[i], jointPos);
		nnInput.push_back(jointPos[0]);
	}
	return nnInput;
}

vector<float> CAT::catInputs() {
	// vestibular system
	vector <float> nnInput;
	vector <float> vInput = vestibularUpdate();
	vector <float> tInput = tactileUpdate();
	vector <float> pInput = proprioUpdate();
	nnInput.insert(nnInput.end(), vInput.begin(), vInput.end());
	nnInput.insert(nnInput.end(), tInput.begin(), tInput.end());
	nnInput.insert(nnInput.end(), pInput.begin(), pInput.end());
	//	cout << "catInputs = " << vInput.size() << endl;
	//	cout << "catInputs = " << tInput.size() << endl;
	//	cout << "catInputs = " << pInput.size() << endl;
	return nnInput;
}

void CAT::update() {
	if (control) {
		vector<float> input; // get sensor parameters
		input = catInputs();
		vector<float> output = control->update(input);
		for (int i = 0; i < output.size(); i++) {
			simSetJointTargetPosition(outputHandles[i], output[i]);
		}
	}
}

vector<int> CAT::getObjectHandles(int parentHandle) {
	simAddObjectToSelection(sim_handle_tree, parentHandle);
	int selectionSize = simGetObjectSelectionSize();
	int tempObjectHandles[1024]; // temporarily stores the object Handles as they cannot be inserted directly in a vector for some reason
	vector<int> objectHandles;
	//s_objectAmount = selectionSize;
	simGetObjectSelection(tempObjectHandles);
	int objectCounter = 0;
	for (size_t i = 0; i < selectionSize; i++)
	{
		if (simGetObjectType(tempObjectHandles[i]) == 0) {
			objectHandles.push_back(tempObjectHandles[i]);
		}
	}
	simRemoveObjectFromSelection(sim_handle_all, -1);
	return objectHandles;
}
vector<int> CAT::getJointHandles(int parentHandle) {
	simAddObjectToSelection(sim_handle_tree, parentHandle);
	int selectionSize = simGetObjectSelectionSize();
	int tempObjectHandles[1024]; // temporarily stores the object Handles as they cannot be inserted directly in a vector for some reason
	vector<int> jointHandles;
	//s_objectAmount = selectionSize;
	simGetObjectSelection(tempObjectHandles);
	int objectCounter = 0;
	for (size_t i = 0; i < selectionSize; i++)
	{
		if (simGetObjectType(tempObjectHandles[i]) == sim_object_joint_type) {
			jointHandles.push_back(tempObjectHandles[i]);
		}
	}
	simRemoveObjectFromSelection(sim_handle_all, -1);
	//cout << "jointHandles size = " << jointHandles.size() << endl;
	return jointHandles;
}

int CAT::getMainHandle() {
	//	catHandle = simGetObjectHandle("Cat_Head");
	return catHandle;
}

void CAT::create() {
	va = shared_ptr<VestibularAttributes>(new VestibularAttributes);

	//#ifdef __linux__ 
	//linux code goes here
	//simLoadModel("C:\\Program Files\\V-REP3\\V-REP_PRO_EDU\\models\\catModel.ttm");
	//#else

	simLoadModel("models/catModel.ttm");
	//#endif
	catHandle = simGetObjectHandle("Cat_Head");
	mainHandle = catHandle;
	floorHandle = simGetObjectHandle("ResizableFloor_5_25");
	vector<int> handles = getObjectHandles(catHandle);
	vector<int> jointHandles = getJointHandles(catHandle);
	feet.clear();
	feet.push_back(simGetObjectHandle("Cat_FootLF"));
	feet.push_back(simGetObjectHandle("Cat_FootRF"));
	feet.push_back(simGetObjectHandle("Cat_FootLB"));
	feet.push_back(simGetObjectHandle("Cat_FootRB"));

	//for (int i = 0; i < 50; i++) {
	//	float size[3] = { 0.055, 0.055, (0.055 * 4) };
	//	simCreatePureShape(0, 1, size, (0.1 * 4), false);
	//}
//	simCreatePureShape(0,0,0,0,0)

	//for (size_t i = 0; i < handles.size(); i++)
	//{
	//	cout << "vector handle [" << i << "] = " << handles[i] << endl;
	//}
	//for (size_t i = 0; i < jointHandles.size(); i++)
	//{
	//	cout << "vector handle [" << i << "] = " << jointHandles[i] << endl;
	//}
	outputHandles.clear();
	for (int i = 0; i < jointHandles.size(); i++) {
		outputHandles.push_back(jointHandles[i]);
		simSetObjectInt32Parameter(jointHandles[i], 2000, 1);
		simSetObjectInt32Parameter(jointHandles[i], 2001, 1);
		simSetObjectFloatParameter(jointHandles[i], 2002, 1);
		simSetObjectFloatParameter(jointHandles[i], 2003, 0.01);
		simSetObjectFloatParameter(jointHandles[i], 2004, 0.0);
		//	sim_jointintparam_ctrl_enabled(2001) : int32 parameter : dynamic motor control loop enable state(0 or != 0)
		//	simSetJointTargetVelocity(joint, 0.2);
		//	simSetJointForce(joint, 100);
		//		simSetJointTargetPosition(jointHandles[i], 1.0);
		simSetJointForce(jointHandles[i], 1.0);
		simSetJointTargetVelocity(jointHandles[i], 0.05);
	}
}