#include "ER_LSystem.h"
#include <iostream>
#include <sstream>


ER_LSystem::ER_LSystem()
{
	modular = true;
}


ER_LSystem::~ER_LSystem()
{
	
}


void ER_LSystem::crossover(shared_ptr<Morphology> partnerMorph, float cr) {
//	cout << "crossing over" << endl;
	shared_ptr<ER_LSystem>morpho(static_pointer_cast<ER_LSystem>(partnerMorph));   //*partnerMorph(ER_LSystem()));
	shared_ptr<LGENOME> tempLGenome;
//	tempLGenome = morpho->lGenome;
	tempLGenome = morpho->lGenome->clone(); 

	bool cross = false;
	for (int i = 0; i < lGenome->amountStates; i++) {
		if (randomNum->randFloat(0, 1) < cr) {
			if (cross == false) {
				cross = true;
			}
			else {
				cross = false;
			}
		}
		if (cross == true) {
//			std::unique_ptr<my_type> ptr2{ new my_type{ *ptr1 } }; // Make deep copy using copy ctor.
//			lGenome->lParameters[i] = tempLGenome->lParameters[i];
			lGenome->lParameters[i] = tempLGenome->lParameters[i]->clone();// unique_ptr<LPARAMETERS>(new tempLGenome->lParameters[i]);
		}
	}
}

void ER_LSystem::printSome() {
	BaseMorphology::printSome();
	cout << "printing some from ER_LSystem" << endl;
}


void ER_LSystem::initializeGenomeCustom(int type)
{
	float red[3] = { 1.0, 0, 0 };
	float blue[3] = { 0.0, 0.0, 1.0 };
	float yellow[3] = { 1.0, 1.0, 0.0 };
	float green[3] = { 0.0, 0.3, 0.0 };
	float orange[3] = { 1.0, 0.5, 0.0 };
	float orangePlus[3] = { 1.0, 0.6, 0.2 };
	float black[3] = { 0.0, 0.0, 0 };
	float pink[3] = { 1.0, 0.5, 0.5 };
	float white[3] = { 1.0, 1.0, 1.0 };

	cout << "initializing custom L-System Genome" << endl;

	morphFitness = 0;
	unique_ptr<ControlFactory> cf = unique_ptr<ControlFactory>(new ControlFactory);

	for (int i = 0; i < lGenome->amountStates; i++) {
		lGenome->lParameters.push_back(shared_ptr<LPARAMETERS>(new LPARAMETERS));
		lGenome->lParameters[i]->currentState = i;
		lGenome->lParameters[i]->type = settings->moduleTypes[i];
		lGenome->lParameters[i]->amountChilds = 0; 
		vector<float>tempVector;

		lGenome->lParameters[i]->control = cf->createNewControlGenome(settings->controlType, settings, randomNum);
		lGenome->lParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons);
		//	cout << "Initializing state modules" << endl; 
		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = pink[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = green[j];
			}
		case 5:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = orange[j];
			}
		default:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = white[j];
			}
			break;

		}

		if (i == 0) {
			lGenome->lParameters[i]->childConfigurations.push_back(1);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
	//		lGenome->lParameters[i]->childConfigurations.push_back(1);
	//		lGenome->lParameters[i]->childSites.push_back(2);
	//		lGenome->lParameters[i]->childSiteStates.push_back(1);
	//		lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
	//		lGenome->lParameters[i]->childConfigurations.push_back(2);
	//		lGenome->lParameters[i]->childSites.push_back(3);
	//		lGenome->lParameters[i]->childSiteStates.push_back(1);
	//		lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//			lGenome->lParameters[i]->childConfigurations.push_back(1);
			//			lGenome->lParameters[i]->childSites.push_back(2);
			//			lGenome->lParameters[i]->childSiteStates.push_back(1);
			//			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			/*	lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(2);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(3);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(4);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();*/
		}
		else if (i == 1) {
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(3);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//			lGenome->lParameters[i]->module = lGenome->moduleFactory->createModuleGenome(4, settings, randomNum);
			//			lGenome->lParameters[i]->childConfigurations.push_back(1);
			//			lGenome->lParameters[i]->childSites.push_back(1);
			//			lGenome->lParameters[i]->childSiteStates.push_back(1);
			//			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//			lGenome->lParameters[i]->module = lGenome->moduleFactory->createModuleGenome(4, settings, randomNum);
			//			lGenome->lParameters[i]->childConfigurations.push_back(1);
			//			lGenome->lParameters[i]->childSites.push_back(2);
			//			lGenome->lParameters[i]->childSiteStates.push_back(1);
			//			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 2) {
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(3);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 3) {
		}
		else if (i == 4) {
		}
		else {
		}
	}
	cf.reset();
}

void ER_LSystem::initializeQuadruped(int type)
{
	float red[3] = { 1.0, 0, 0 };
	float blue[3] = { 0.0, 0.0, 1.0 };
	float yellow[3] = { 1.0, 1.0, 0.0 };
	float green[3] = { 0.0, 0.3, 0.0 };
	float orange[3] = { 1.0, 0.5, 0.0 };
	float orangePlus[3] = { 1.0, 0.6, 0.2 };
	float black[3] = { 0.0, 0.0, 0 };
	float pink[3] = { 1.0, 0.5, 0.5 };
	float white[3] = { 1.0, 1.0, 1.0 };

	cout << "initializing Quadruped L-System Genome" << endl;

	morphFitness = 0;
	unique_ptr<ControlFactory> cf = unique_ptr<ControlFactory>(new ControlFactory);

	for (int i = 0; i < lGenome->amountStates; i++) {
		lGenome->lParameters.push_back(shared_ptr<LPARAMETERS>(new LPARAMETERS));
		lGenome->lParameters[i]->currentState = i;
		if (i == 0) {
			lGenome->lParameters[i]->type = 1;
		}
		else if (i == 4) {
			lGenome->lParameters[i]->type = 12;
		}
		else {
			lGenome->lParameters[i]->type = 4;
		}
		lGenome->lParameters[i]->amountChilds = 0;
		vector<float>tempVector;

		lGenome->lParameters[i]->control = cf->createNewControlGenome(settings->controlType, settings, randomNum);
		lGenome->lParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons);
		//	cout << "Initializing state modules" << endl; 
		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = pink[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = green[j];
			}
		case 5:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = orange[j];
			}
		default:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = white[j];
			}
			break;
		}

		if (i == 0) {
			// head
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(4);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			
			// servos
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(4);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(1);
			lGenome->lParameters[i]->childSiteStates.push_back(2);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(2);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(3);
			lGenome->lParameters[i]->childSiteStates.push_back(2);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			
			//		lGenome->lParameters[i]->childConfigurations.push_back(1);
			//		lGenome->lParameters[i]->childSites.push_back(2);
			//		lGenome->lParameters[i]->childSiteStates.push_back(1);
			//		lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//		lGenome->lParameters[i]->childConfigurations.push_back(2);
			//		lGenome->lParameters[i]->childSites.push_back(3);
			//		lGenome->lParameters[i]->childSiteStates.push_back(1);
			//		lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//			lGenome->lParameters[i]->childConfigurations.push_back(1);
			//			lGenome->lParameters[i]->childSites.push_back(2);
			//			lGenome->lParameters[i]->childSiteStates.push_back(1);
			//			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			/*	lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(2);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(3);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(4);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();*/
		}
		else if (i == 1) {
			lGenome->lParameters[i]->childConfigurations.push_back(1);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(3);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//			lGenome->lParameters[i]->module = lGenome->moduleFactory->createModuleGenome(4, settings, randomNum);
			//			lGenome->lParameters[i]->childConfigurations.push_back(1);
			//			lGenome->lParameters[i]->childSites.push_back(1);
			//			lGenome->lParameters[i]->childSiteStates.push_back(1);
			//			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//			lGenome->lParameters[i]->module = lGenome->moduleFactory->createModuleGenome(4, settings, randomNum);
			//			lGenome->lParameters[i]->childConfigurations.push_back(1);
			//			lGenome->lParameters[i]->childSites.push_back(2);
			//			lGenome->lParameters[i]->childSiteStates.push_back(1);
			//			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 2) {
			lGenome->lParameters[i]->childConfigurations.push_back(1);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(3);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 3) {
		}
		else if (i == 4) {
		}
		else {
		}
	}
	cf.reset();
}

void ER_LSystem::initializeSolar(int type)
{

	float red[3] = { 1.0, 0, 0 };
	float blue[3] = { 0.0, 0.0, 1.0 };
	float yellow[3] = { 1.0, 1.0, 0.0 };
	float green[3] = { 0.0, 0.3, 0.0 };
	float orange[3] = { 1.0, 0.5, 0.0 };
	float orangePlus[3] = { 1.0, 0.6, 0.2 };
	float black[3] = { 0.0, 0.0, 0 };
	float pink[3] = { 1.0, 0.5, 0.5 };
	float white[3] = { 1.0, 1.0, 1.0 };

	cout << "initializing Quadruped L-System Genome" << endl;

	morphFitness = 0;
	unique_ptr<ControlFactory> cf = unique_ptr<ControlFactory>(new ControlFactory);

	for (int i = 0; i < lGenome->amountStates; i++) {
		lGenome->lParameters.push_back(shared_ptr<LPARAMETERS>(new LPARAMETERS));
		lGenome->lParameters[i]->currentState = i;
		if (i == 0) {
			lGenome->lParameters[i]->type = 8;
		}
		else if (i == 4) {
			lGenome->lParameters[i]->type = 11;
		}
		else {
			lGenome->lParameters[i]->type = 4;
		}
		lGenome->lParameters[i]->amountChilds = 0;
		vector<float>tempVector;

		lGenome->lParameters[i]->control = cf->createNewControlGenome(settings->controlType, settings, randomNum);
		lGenome->lParameters[i]->control->init(6, 1, 2);
		//	cout << "Initializing state modules" << endl; 
		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = pink[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = green[j];
			}
		case 5:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = orange[j];
			}
		default:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = white[j];
			}
			break;
		}

		if (i == 0) {
			// head
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(1);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 1) {
			lGenome->lParameters[i]->childConfigurations.push_back(1);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(2);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 2) {
			lGenome->lParameters[i]->childConfigurations.push_back(1);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(4);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 3) {
		}
		else if (i == 4) {
		}
		else {
		}
	}
	settings->morphMutRate = -0.1;
	cf.reset();
}


const std::string ER_LSystem::generateGenome(int indNum, float fitness) const
{
//	cout << "saving lGenome " << indNum << " in folder " << sceneNum << ", that had a fitness of " << fitness << endl << "-------------------------------- "<< endl;
//	int evolutionType = 0; // regular evolution, will be changed in the future. 
	int amountCreatedModules = createdModules.size(); 
	int amountStates = lGenome->lParameters.size(); 

	ostringstream genomeText;
	genomeText << "#Individual:" << indNum << endl; 
	genomeText << "#Fitness:," << fitness << endl;
	genomeText << "#phenValue;," << phenValue << endl;
	genomeText << "#AmountStates:," << amountStates << "," << endl << endl;
//	cout << "#AmountStates:," << amountStates << "," << endl << endl;

	genomeText << "Module Parameters Start Here: ," << endl << endl;
	for (int i = 0; i < amountStates; i++) {
		if (settings->verbose) {
			cout << "Receiving genome parameters of module " << i << endl;
		}
		genomeText << "#Module:," << i << endl;
		genomeText << "#ModuleType:," << lGenome->lParameters[i]->type << endl;
		genomeText << "#ModuleState:," << lGenome->lParameters[i]->currentState << endl; 
		if (settings->verbose) {
			cout << "Module "<< i << " has " << lGenome->lParameters[i]->amountChilds << " child modules attached to it" << endl;		
			cout << " - childSites.size() is " << lGenome->lParameters[i]->childSites.size() << endl;
			cout << " - childConfigurations.size() is " << lGenome->lParameters[i]->childConfigurations.size() << endl;
			cout << " - childSiteStates.size() is " << lGenome->lParameters[i]->childSiteStates.size() << endl;
		}

		genomeText << "#AmountChilds:," << lGenome->lParameters[i]->amountChilds << endl;
		genomeText << "#ChildSites:,";
		for (int j = 0; j < lGenome->lParameters[i]->childSites.size(); j++) {
			genomeText << lGenome->lParameters[i]->childSites[j] << ",";
		} genomeText << endl; 
		genomeText << "#ChildConfigurations:,";
		for (int j = 0; j < lGenome->lParameters[i]->childConfigurations.size(); j++) {
			genomeText << lGenome->lParameters[i]->childConfigurations[j] << ",";
		} genomeText << endl;
		genomeText << "#ChildSiteStates:,";
		for (int j = 0; j < lGenome->lParameters[i]->childSiteStates.size(); j++) {
			genomeText << lGenome->lParameters[i]->childSiteStates[j] << ",";
		} genomeText << endl;
//		genomeText << "," << lGenome->lParameters[i]->moduleType << ",";
		if (settings->verbose) {
			cout << "Getting control parameters of module " << i << endl;
		}
		genomeText << "#ControlParams:," << endl;
		genomeText << lGenome->lParameters[i]->control->getControlParams().str(); 

		genomeText << "#EndOfModule," << endl << endl;
		if (settings->verbose) {
			cout << "All parameters of module " << i << " were correctly received << endl" << endl;
		}
	}

	return genomeText.str();
}

float ER_LSystem::getFitness() {
	return fitness;
}

bool ER_LSystem::loadGenome(std::istream &genomeInput, int individualNumber)
{
	if (settings->verbose) {
		cout << "loading genome " << individualNumber << "(ER_LSystem)" << endl;
	}

//	cout << "loading genome " << individualNumber << endl;
	lGenome = std::shared_ptr<LGENOME>(new LGENOME);
//	lGenome->lParameters.clear();
//	cout << "lGenome cleared" << endl;

	string value;
	list<string> values;
	while (genomeInput.good())
	{
		getline(genomeInput, value, ',');
		//		cout << value << ",";
		if (value.find('\n') != string::npos) {
			split_line(value, "\n", values);
		}
		else {
			values.push_back(value);
		}
	}

	int moduleNum;
	vector<string> moduleValues;
	vector<string> controlValues;
	bool checkingModule = false;
	bool checkingControl = false; 

	list<string>::const_iterator it = values.begin();
	for (it = values.begin(); it != values.end(); it++) {
		string tmp = *it;
	//	cout << "tmp = " << tmp << endl;
		if (checkingModule == true) {
			moduleValues.push_back(tmp);
		}
		if (checkingControl == true) {
			controlValues.push_back(tmp);
		}
		if (tmp == "#Fitness:") {
			it++;
			tmp = *it;
			fitness = atof(tmp.c_str());
	//		cout << "Fitness was " << fitness << endl; 
		}
		if (tmp == "#phenValue;") {
			it++;
			tmp = *it;
			phenValue = atof(tmp.c_str());
		}
		else if (tmp == "#AmountStates:") {
			it++;
			tmp = *it;
			lGenome->amountStates = atoi(tmp.c_str());
			for (int i = 0; i < lGenome->amountStates; i++) {
				lGenome->lParameters.push_back(shared_ptr<LPARAMETERS>(new LPARAMETERS));
			}
		}
		if (tmp == "#Module:") {
			it++;
			tmp = *it;
			moduleNum = atoi(tmp.c_str());
			checkingModule = true; 
	//		cout << "moduleNum set to " << moduleNum << endl; 
		}
		else if (tmp == "#AmountChilds:") {
			it++;
			tmp = *it;
			int ac = atoi(tmp.c_str());
			lGenome->lParameters[moduleNum]->amountChilds = ac;
			lGenome->lParameters[moduleNum]->childSites.resize(ac);
			lGenome->lParameters[moduleNum]->childConfigurations.resize(ac);
			lGenome->lParameters[moduleNum]->childSiteStates.resize(ac);
		}
		else if (tmp == "#ChildSites:") {
			for (int i = 0; i < lGenome->lParameters[moduleNum]->amountChilds; i++) {
				it++;
				tmp = *it;
				lGenome->lParameters[moduleNum]->childSites[i] = atoi(tmp.c_str());
			}
		}
		else if (tmp == "#ChildConfigurations:") {
			for (int i = 0; i < lGenome->lParameters[moduleNum]->amountChilds; i++) {
				it++;
				tmp = *it;
				lGenome->lParameters[moduleNum]->childConfigurations[i] = atoi(tmp.c_str());
			}
		}
		else if (tmp == "#ChildSiteStates:") {
	//		cout << "loading childSiteStates" << endl;
			for (int i = 0; i < lGenome->lParameters[moduleNum]->amountChilds; i++) {
				it++;
				tmp = *it;
				lGenome->lParameters[moduleNum]->childSiteStates[i] = atoi(tmp.c_str());
			}
		}
		else if (tmp == "#ModuleType:") {
			it++;
			tmp = *it;
	//		cout << "creating module of type: " << atoi(tmp.c_str()) << endl; 
			lGenome->lParameters[moduleNum]->type = atoi(tmp.c_str());
			lGenome->lParameters[moduleNum]->currentState = moduleNum;
	//		cout << "state = " << lGenome->lParameters[moduleNum].module->state << endl;
		}
		if (tmp == "#ControlParams:") {
			checkingControl = true; 
		}
		else if (tmp == "#EndOfModule") {
			// this is not right: change it 
//			lGenome->lParameters[moduleNum]->module->setModuleParams(moduleValues);
			moduleValues.clear(); 
			if (checkingControl == true) {
				unique_ptr<ControlFactory> controlFactory(new ControlFactory);
				lGenome->lParameters[moduleNum]->control = controlFactory->createNewControlGenome(atoi(controlValues[2].c_str()), settings, randomNum); // 0 is ANN
			//	lGenome->lParameters[moduleNum]->control->init(1, 2, 1);
				lGenome->lParameters[moduleNum]->control->setControlParams(controlValues);
				checkingControl = false;
				controlValues.clear(); 
				controlFactory.reset();
			}
			moduleNum++;
			checkingModule = false; 
		}
	}

	// setting color
	float red[3] = { 1.0, 0, 0 };
	float blue[3] = { 0.0, 0.0, 1.0 };
	float yellow[3] = { 1.0, 1.0, 0.0 };
	float green[3] = { 0.0, 0.3, 0.0 };
	float orange[3] = { 1.0, 0.5, 0.0 };
	float orangePlus[3] = { 1.0, 0.6, 0.2 };
	float black[3] = { 0.0, 0.0, 0 };
	float pink[3] = { 1.0, 0.5, 0.5 };
	float white[3] = { 0.95,0.95,0.95 };
	float grey[3] = { 0.45,0.45,0.45 };


	//	lGenome->lParameters.resize(lGenome->amountStates);
	//	cout << "amount of states = " << lGenome->amountStates << endl; 
	morphFitness = 0;
	for (int i = 0; i < lGenome->amountStates; i++) {
		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = pink[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = red[j];
			}
			break;
		case 5:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = yellow[j];
			}
			break;
		default:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = grey[j];
			}
			break;
		}
		lGenome->lParameters[i]->moduleColor[0] = lGenome->lParameters[i]->color[0];
		lGenome->lParameters[i]->moduleColor[1] = lGenome->lParameters[i]->color[1];
		lGenome->lParameters[i]->moduleColor[2] = lGenome->lParameters[i]->color[2];
	}

	// TODO: Check if code below is necessary
	unique_ptr<ModuleFactory> mf = unique_ptr<ModuleFactory>(new ModuleFactory);
	for (int i = 0; i < lGenome->lParameters.size(); i++) {
		shared_ptr<ER_Module> mod = mf->createModuleGenome(lGenome->lParameters[i]->type, settings, randomNum);
		mod->state = i;
		mod->type = settings->moduleTypes[i];
		mod->control = lGenome->lParameters[i]->control;
		modules.push_back(mod);
	}
	mf.reset();

	return true;
//	cout << "loaded L-System genome" << endl;
}



void ER_LSystem::init() {
	lGenome = shared_ptr<LGENOME>(new LGENOME);
	maxModuleTypes = settings->maxModuleTypes;
	if (settings->evolutionType != settings->EMBODIED_EVOLUTION && settings->morphologyType != settings->QUADRUPED_GENERATIVE
		&& settings->morphologyType != settings->CUSTOM_SOLAR_GENERATIVE) {
		//		initializeGenomeCustom(0);
		initializeLGenome(0);
	}
	if (settings->morphologyType == settings->QUADRUPED_GENERATIVE) {
		initializeQuadruped(0);
	}
	else if (settings->morphologyType == settings->CUSTOM_SOLAR_GENERATIVE) {
		initializeSolar(0);
	}
	else {
		//		initializeLRobot(0);
	}
	if (settings->verbose) {
		std::cout << "Done initializing L-Genome" << std::endl;
	}
	// set the modules to be used by the L-System
	unique_ptr<ModuleFactory> mf = unique_ptr<ModuleFactory>(new ModuleFactory);
	for (int i = 0; i < settings->amountModules; i++) {
		modules.push_back(mf->createModuleGenome(settings->moduleTypes[i], settings, randomNum));
		modules[i]->state = i;
		modules[i]->type = lGenome->lParameters[i]->type;
		modules[i]->control = lGenome->lParameters[i]->control;
	}
	mf.reset();
}



int ER_LSystem::initializeLGenome(int type) {
	//first read settings
	lGenome->amountIncrement = settings->lIncrements;
	lGenome->amountStates = settings->amountModules;
	lGenome->maxAmountStates = settings->maxAmountModules; // states *

	float red[3] = { 1.0, 0, 0 };
	float blue[3] = { 0.0, 0.0, 1.0 };
	float yellow[3] = { 1.0, 1.0, 0.0 };
	float green[3] = { 0.0, 0.3, 0.0 };
	float orange[3] = { 1.0, 0.5, 0.0 };
	float orangePlus[3] = { 1.0, 0.6, 0.2 };
	float black[3] = { 0.0, 0.0, 0 };
	float pink[3] = { 1.0, 0.5, 0.5 };
	float white[3] = { 1.0, 1.0, 1.0 };
	
	morphFitness = 0;
	unique_ptr<ControlFactory> cf = unique_ptr<ControlFactory>(new ControlFactory);
	for (int i = 0; i < lGenome->amountStates; i++) {
		lGenome->lParameters.push_back(shared_ptr<LPARAMETERS>(new LPARAMETERS));
		lGenome->lParameters[i]->type = settings->moduleTypes[i];
		vector<float>tempVector;
		// cout << "Initializing state modules" << endl; 
		// currently everything has a neural network...
		lGenome->lParameters[i]->control = cf->createNewControlGenome(settings->controlType, settings, randomNum);
		if (settings->controlType == settings->ANN_DISTRIBUTED_BOTH) {
			lGenome->lParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons); // 2 additional inputs and outputs used fotr 
		}
		else if (settings->controlType == settings->ANN_DISTRIBUTED_UP) {
			lGenome->lParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons); // 2 additional inputs and outputs used fotr 
		}
		else if (settings->controlType == settings->ANN_DISTRIBUTED_DOWN) {
			lGenome->lParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons); // 2 additional inputs and outputs used fotr 
		}
		else {
			lGenome->lParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons); // still two additional outputs
		}
	
		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = pink[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = green[j];
			}
		case 5:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = orange[j];
			}
		default:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = white[j];
			}
			break;
		}

		lGenome->lParameters[i]->currentState = i;

	}
	mutateERLGenome(0.5);
	cf.reset();
	return 1;
}

shared_ptr<Morphology> ER_LSystem::clone() const {
	BaseMorphology::clone();
	shared_ptr<ER_LSystem> ur = make_unique<ER_LSystem>(*this);
	ur->lGenome = this->lGenome->clone();
	//for (int i = 0; i < ur->lGenome->lParameters.size(); i++) {
	//	ur->lGenome->lParameters[i] = this->lGenome->lParameters[i]->clone();
	//}
	return ur;
}


int ER_LSystem::getNewSite(int maxCh, int currentSite, vector<int> sites) {
	if (maxCh == sites.size()) {
		// all other sites are occupied, so the site cannot be changed. 
		return currentSite;
	}
	int newSite = -1;
	bool uniqueSite = false;
	while (uniqueSite == false) {
		// will never exit the loop until a unique site is found. 
		newSite = randomNum->randInt(maxCh, 0);
		uniqueSite = true; // if the site is not unique, it will be set by the next for loop.
		for (int i = 0; i < sites.size(); i++) {
			if (sites[i] == newSite) {
				// this site is already taken so try again
				uniqueSite = false;
				break;
			}
		}

	}
	return newSite;
}

int ER_LSystem::mutateERLGenome(float mutationRate) {
	if (settings->verbose) {
		std::cout << "Mutating L-Genome" << std::endl;
	}
	mutateControlERLGenome(mutationRate);
	for (int i = 0; i < lGenome->lParameters.size(); i++) {
		if (settings->verbose) {
			std::cout << "l " << i << std::endl;
		}
		// mutate the controller. 
		if (!lGenome->lParameters[i]->control) {
			std::cerr << "control = null? Check ER_LSystem.cpp" << std::endl;
		}
		//lGenome->lParameters[i]->control->mutate(settings->mutationRate);

		// Resize the rules (Potentially very destructive) 
		int childSize = lGenome->lParameters[i]->childSites.size();

		if (randomNum->randFloat(0.0, 1.0) < mutationRate) { // randomly change amount childs, very destructive mutation
			int maxCh = 0;
			maxCh = getMaxChilds(lGenome->lParameters[i]->type);
			if (settings->verbose) {
				cout << "maxCh of module " << i << " is " << maxCh << endl;
			}
			if (maxCh != 0) {
				int newChildSize = randomNum->randInt(maxCh + 1, 0);
				if (settings->verbose) {
					std::cout << "newChildSize = " << newChildSize << std::endl;
					std::cout << "site vector size = " << lGenome->lParameters[i]->childSites.size() << std::endl;
				}
				while (lGenome->lParameters[i]->childSites.size() < newChildSize) {
					if (settings->verbose) {
						std::cout << "while" << std::endl;
					}
					// TODO make another object containing child site, state and orientation. Struct?
					vector<int> sitebuffer = lGenome->lParameters[i]->childSites;
					lGenome->lParameters[i]->childSites.push_back(getNewSite(maxCh, -1, sitebuffer));
					lGenome->lParameters[i]->childSiteStates.push_back(randomNum->randInt(lGenome->amountStates, 0));
					lGenome->lParameters[i]->childConfigurations.push_back(randomNum->randInt(4,0));
				}
				if (settings->verbose) {
					std::cout << "size = " << lGenome->lParameters[i]->childSites.size() << std::endl;
				}
				else if (lGenome->lParameters[i]->childSites.size() > newChildSize) {
					if (settings->verbose) {
						std::cout << "erasing" << std::endl;
					}
					while (lGenome->lParameters[i]->childSites.size() > newChildSize) { // now removes random site
						int rSite = randomNum->randInt(lGenome->lParameters[i]->childSites.size(), 0);
						lGenome->lParameters[i]->childSites.erase(lGenome->lParameters[i]->childSites.begin() + rSite);
						lGenome->lParameters[i]->childSiteStates.erase(lGenome->lParameters[i]->childSiteStates.begin() + rSite);
						lGenome->lParameters[i]->childConfigurations.erase(lGenome->lParameters[i]->childConfigurations.begin() + rSite);
					}
				}
			}
			if (settings->verbose) {
				std::cout << "size = " << lGenome->lParameters[i]->childSites.size() << std::endl;
			}
			// mutate the sites
			for (int j = 0; j < lGenome->lParameters[i]->childSites.size(); j++) {
				if (settings->verbose) {
					std::cout << "j = " << j << std::endl;
				}
				if (randomNum->randFloat(0.0, 1.0) < mutationRate) { // change child configuration and state at random
					if (maxCh != 0) {
						if (settings->verbose) {
							std::cout << "randomizing" << std::endl;
						}
						lGenome->lParameters[i]->childSites[j] = getNewSite(maxCh, lGenome->lParameters[i]->childSites[j], lGenome->lParameters[i]->childSites);
						lGenome->lParameters[i]->childSiteStates[j] = randomNum->randInt(lGenome->amountStates,0);
						lGenome->lParameters[i]->childConfigurations[j] = randomNum->randInt(4, 0);
					}
				}
				if (randomNum->randFloat(0.0, 1.0) < mutationRate) { // swap sites
					if (maxCh >= 2) {
						int swapCandidate = randomNum->randInt(lGenome->lParameters[i]->childSites.size(), 0);
						if (j != swapCandidate) { 
							if (settings->verbose) {
								std::cout << "swapping" << std::endl;
							}
							int siteSwapCandidateBuffer = lGenome->lParameters[i]->childSites[swapCandidate];
							int stateSwapCandidateBuffer = lGenome->lParameters[i]->childSiteStates[swapCandidate];
							int configurationSwapCandidateBuffer = lGenome->lParameters[i]->childConfigurations[swapCandidate];
							if (settings->verbose) {
								std::cout << "changing candidate" << std::endl;
							}
							// change swapCandidate
							lGenome->lParameters[i]->childSites[swapCandidate] = lGenome->lParameters[i]->childSites[j];
							lGenome->lParameters[i]->childSiteStates[swapCandidate] = lGenome->lParameters[i]->childSiteStates[j];
							lGenome->lParameters[i]->childConfigurations[swapCandidate] = lGenome->lParameters[i]->childConfigurations[j];
							if (settings->verbose) {
								std::cout << "changing j" << std::endl;
							}
							// change j for swapCandidate using buffer. 
							lGenome->lParameters[i]->childSites[j] = siteSwapCandidateBuffer;
							lGenome->lParameters[i]->childSiteStates[j] = stateSwapCandidateBuffer;
							lGenome->lParameters[i]->childConfigurations[j] = configurationSwapCandidateBuffer;
						}
					}
				}
			}
		}
		lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		if (settings->verbose) {
			std::cout << "Done mutating L-Genome parameters of " << i << std::endl;
		}

	//	cout << "size = " << lGenome->lParameters[i]->childSites.size() << endl;

	}
	if (settings->verbose) {
		std::cout << "Mutated L-Genome "<< std::endl;
	}
//	symmetryMutation(settings->morphMutRate);
	return 1;
}

int ER_LSystem::mutateControlERLGenome(float mutationRate) {
	if (settings->verbose) {
		cout << "mutating l-genome control" << endl;
	}
	for (int i = 0; i < lGenome->lParameters.size(); i++) {
		if (settings->verbose) {
			cout << "mutating " << i + 1 << " out of " << lGenome->lParameters.size() << endl;
		}

		lGenome->lParameters[i]->control->mutate(mutationRate);
	}
	if (settings->verbose) {
		cout << "Done mutating control" << endl;
	}

	return 1;
}

void ER_LSystem::mutate() {
	mutateERLGenome(settings->morphMutRate);
}

void ER_LSystem::checkGenome(int individualNumber, int sceneNum) {
	cout << "checkingGenome" << endl;
	ostringstream genomeFileName;
	genomeFileName << "interfaceFiles\\genomes" << sceneNum << "\\genome" << individualNumber << ".csv";
	ifstream genomeFile(genomeFileName.str());
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
	int moduleNum;
	vector<string> moduleValues;
	vector<string> controlValues;
	bool checkingModule = false;
	bool checkingControl = false;

	list<string>::const_iterator it = values.begin();
	for (it = values.begin(); it != values.end(); it++) {
		string tmp = *it;
		//	cout << "tmp = " << tmp << endl;
		if (checkingModule == true) {
			moduleValues.push_back(tmp);
		}
		if (checkingControl == true) {
			controlValues.push_back(tmp);
		}
		
		if (tmp == "#Module:") {
			it++;
			tmp = *it;
			moduleNum = atoi(tmp.c_str());
			checkingModule = true;
			//		cout << "moduleNum set to " << moduleNum << endl; 
		}
		if (tmp == "#ControlParams:") {
			checkingControl = true;
		}
		else if (tmp == "#EndOfModule") {
		//	lGenome->lParameters[moduleNum].module->setModuleParams(moduleValues);
			moduleValues.clear();
			// cannot check control in this version
			moduleNum++;
			checkingModule = false;
		}
	}
	cout << "checked L-System genome" << endl;
}

void ER_LSystem::checkControl(int individual, int sceneNum) {
	checkGenome(individual, sceneNum);
}



void ER_LSystem::createAtPosition(float x, float y, float z) {
	cout << "x, y, z: " << x << ", " << y << ", " << z << endl;
	float position[3];
	//setColors();
	position[0] = x;
	position[1] = y;
	position[2] = z;
	positionFirstObject[0] = x;
	positionFirstObject[1] = y;
	positionFirstObject[2] = z;
	create();
	//	initializeLSystem(settings->lIncrements, position); // / amount increment is not in genome anymore
}


void ER_LSystem::incrementLSystem() {
	unique_ptr<ModuleFactory> mf = unique_ptr<ModuleFactory>(new ModuleFactory);
	if (settings->verbose) {
		std::cout << "Incrementing L-System" << std::endl;
	}
	int length_i = createdModules.size();
	//	cout << "length_i = " << length_i << endl; 
	for (int i = 0; i < length_i; i++) {
		if (createdModules[i]->handled != true) {
			createdModules[i]->handled = true;
			if (createdModules.size() >= settings->maxAmountModules) {
				break;
			}
			// cout << "handling module " << i << endl; 
			// So in the direct encoding I can set the parent site. 
			// In the L-System however, the parent site contains the information of the children. 
			vector<int> tempFreeSites;
			int t_state = createdModules[i]->state; // temp save state
		//	cout << "t_state = " << t_state << endl; 
			// I think I used tempFreeSites so things can grow...
			tempFreeSites = createdModules[i]->getFreeSites(lGenome->lParameters[t_state]->childSites);
			//	cout << "childSites.length = " << lGenome->lParameters[t_state]->childSites.size() << endl;
			//	cout << "Amount Free Sites: " << tempFreeSites.size() << endl; 
			//	cout << "lGenome->lParameters[t_state]->childSites.size() = " << lGenome->lParameters[t_state]->childSites.size() << endl; 
			//	cout << "created module sites: " << createdModules[i]->sites.size() << endl;
			//	cout << "created module free sites: " << createdModules[i]->freeSites.size() << endl;
			int newChildAmount = 0;
			for (int j = 0; j < tempFreeSites.size(); j++) { // should never be more then free sites of module
				if (createdModules.size() >= settings->maxAmountModules) {
					break;
				}
				for (int k = 0; k < lGenome->lParameters[t_state]->childSites.size(); k++) {
					if (createdModules.size() >= settings->maxAmountModules) {
						break;
					}
					if (lGenome->lParameters[t_state]->childSites.size() != lGenome->lParameters[t_state]->childSiteStates.size()) {
						std::cerr << "ERROR: childSiteStates not correct length" << std::endl;
						std::cerr << "childSite length = " << lGenome->lParameters[t_state]->childSites.size() << std::endl;
						std::cerr << "childSiteStates length = " << lGenome->lParameters[t_state]->childSiteStates.size() << std::endl;
					}
					int childSiteState = lGenome->lParameters[t_state]->childSiteStates[k];
					//					int childType = lGenome->lParameters[childSiteState]->type;
					int childType = modules[childSiteState]->type;
					int maxMs = 100; // this is set so it cannot try to create more than 100 modules. TODO: should be defined elsewhere
					for (int s = 0; s < settings->maxModuleTypes.size(); s++) {
						if (settings->maxModuleTypes[s][0] == childType) {
							maxMs = settings->maxModuleTypes[s][1];
							break;
						}
					}
					int maxCurMs = 0;
					for (int s = 0; s < createdModules.size(); s++) {
						if (createdModules[s]->type == childType) {
							maxCurMs++;
						}
					}
					if (maxCurMs < maxMs) {
						if (lGenome->lParameters[t_state]->childSites[k] == tempFreeSites[j]) {
							int childSite = lGenome->lParameters[t_state]->childSites[k];
							int parentHandle = createdModules[i]->siteConfigurations[childSite][0]->parentHandle;
							int relativePositionHandle = createdModules[i]->siteConfigurations[childSite][0]->relativePosHandle;
							newChildAmount++;
							// to make sure they are connected properly
							bool par = false;
							for (int z = 0; z < createdModules[i]->objectHandles.size(); z++) {
								if (parentHandle == createdModules[i]->objectHandles[z]) {
									par = true;
								}
							}
							if (par == false) {
								std::cerr << "The L-system encountered a problem with not being able to find the parent handle" << std::endl;
								break;
							}

							//	cout << "childSite: " << childSite << endl; 
							/*	cout << "feesites?" << endl;
								cout << "created module sites: " << createdModules[i]->sites.size() << endl;
								cout << "created module free sites: " << createdModules[i]->freeSites.size() << endl;
								cout << "i + j + newChildAmount = " << i + j + newChildAmount << endl;
								cout << "newChildAmount = " << newChildAmount << endl;

								*/
							int childModuleNum = i + newChildAmount;
							//	cout << "childModuleNum: " << childModuleNum << endl; 
						// UNCOMMENT!!!!!!!!!!!!!!! TO DO
							//createdModules[i]->freeSites[j] = -1;
						//					lGenome->lParameters[t_state]->childSites[k] = -1;
										//	cout << "attachmentSites[k] == tempFreeSites[j]!!" << endl; 
										//	cout << "config = " << lGenome->lParameters[t_state]->childConfigurations[k] << endl; 

							int config = lGenome->lParameters[t_state]->childConfigurations[k];
							vector<float> siteConfiguration;
							siteConfiguration.push_back(createdModules[i]->siteConfigurations[tempFreeSites[j]][config]->x);
							siteConfiguration.push_back(createdModules[i]->siteConfigurations[tempFreeSites[j]][config]->y);
							siteConfiguration.push_back(createdModules[i]->siteConfigurations[tempFreeSites[j]][config]->z);
							siteConfiguration.push_back(createdModules[i]->siteConfigurations[tempFreeSites[j]][config]->rX);
							siteConfiguration.push_back(createdModules[i]->siteConfigurations[tempFreeSites[j]][config]->rY);
							siteConfiguration.push_back(createdModules[i]->siteConfigurations[tempFreeSites[j]][config]->rZ);
							createdModules.push_back(mf->copyModuleGenome(modules[childSiteState]));
							int createdModulesSize = createdModules.size();
							vector<float> configuration;
							configuration.resize(6);
							for (int w = 0; w < 6; w++) {
								configuration[w] = siteConfiguration[w];
							}

							createdModules[createdModulesSize - 1]->createModule(configuration, relativePositionHandle, parentHandle);
							// set color
							createdModules[createdModulesSize - 1]->colorModule(lGenome->lParameters[childSiteState]->color, 1.0);
							createdModules[createdModulesSize - 1]->parentModulePointer = createdModules[i];
							createdModules[createdModulesSize - 1]->parent = i;
							createdModules[createdModulesSize - 1]->parentSite = childSite;
							createdModules[createdModulesSize - 1]->orientation = config;
							vector<int> exception;
							exception.push_back(parentHandle);
							for (int p = 0; p < createdModules[createdModulesSize - 1]->objectHandles.size(); p++) {
								exception.push_back(createdModules[createdModulesSize - 1]->objectHandles[p]);
							}
							if (checkLCollisions(createdModules[createdModulesSize - 1], exception) == true) {
								//			cout << "COLLISION: Removing module" << endl; 
										//	createdModules[createdModulesSize - 1]->removeModule(); // automatically called when pointer is erased
								createdModules[createdModulesSize - 1]->removeModule();
								createdModules.pop_back();
								//	createdModules.erase(createdModules.begin() + (createdModulesSize - 1));
								newChildAmount--;
								//			cout << "newChildAmount = " << newChildAmount << endl; 
							}
							else if (settings->environmentType == settings->ENV_SWITCHOBJECTIVE && simGetSimulationTime() < 10) {
								if (createdModules[createdModulesSize - 1]->type == 11) {
									// cout << "Removing type 11 " << endl;
									createdModules[createdModulesSize - 1]->removeModule();
									createdModules.pop_back();
									//	createdModules.erase(createdModules.begin() + (createdModulesSize - 1));
									newChildAmount--;
								}
							}
							else {
								// environment collision with all object handles does not work very well. 
								/*cout << "env" << endl;
								for (int i = 0; i < createdModules[createdModules.size() - 1]->objectHandles.size(); i++) {
									environment->envObjectHandles.push_back(createdModules[createdModules.size() - 1]->objectHandles[i]);
								}*/
								// set control
					//			createdModules[createdModulesSize - 1]->createControl();
					//			cout << "No Collision" << endl; 
							}
							//					if (createdModules[createdModules.size() - 1]->objectHandles.size() > 4) {
							//						cout << "break" << endl;
							//					}
												//	CollisionDetector* Col = new CollisionDetector();
											//	Col->checkCollision(createdModules[i + j + 1]->objectHandles[0]);
												//break; 
						}
					}
					else {
						//	newChildAmount--;
					}
				}
			}
		}
	}
	mf.reset();
	//	cout << endl;
}



void ER_LSystem::checkForceSensors() {
	for (int i = 0; i < createdModules.size(); i++) {
		if (createdModules[i]->broken != true) {
			for (int j = 0; j < createdModules[i]->objectHandles.size(); j++) {
				if (simGetObjectType(createdModules[i]->objectHandles[j]) == sim_object_forcesensor_type) {
					int force = simReadForceSensor(createdModules[i]->objectHandles[j], NULL, NULL);
					if (force != 0 && force != -1) {
						if (force == 3) {
							cout << "force sensor is broken" << endl;
							cout << "module " << i << " is broken" << endl;
							createdModules[i]->broken = true;
						}
					}
				}
			}
		}
	}
}

void ER_LSystem::savePhenotype(int ind, float fitness)
{
	// change createdModules back to a moduleParameters array. 
	vector<shared_ptr<BASEMODULEPARAMETERS>> bmp;
	for (int i = 0; i < createdModules.size(); i++) {
		bmp.push_back(shared_ptr<BASEMODULEPARAMETERS>(new BASEMODULEPARAMETERS));
		bmp[i]->control = createdModules[i]->control; // no deep copy needed since created modules will be deleted
		bmp[i]->type = createdModules[i]->type;
		bmp[i]->parent = createdModules[i]->parent;
		bmp[i]->parentSite = createdModules[i]->parentSite;
		bmp[i]->orientation = createdModules[i]->orientation;
	}
	Development::savePhenotype(bmp, ind, fitness);
}

void ER_LSystem::initializeLRobot(int type) {
	//srand(rand()%100000);
	shared_ptr<ModuleFactory> mf = shared_ptr<ModuleFactory>(new ModuleFactory);

	float red[3] = { 1.0, 0, 0 };
	float blue[3] = { 0.0, 0.0, 1.0 };
	float yellow[3] = { 1.0, 1.0, 0.0 };
	float green[3] = { 0.0, 0.3, 0.0 };
	float orange[3] = { 1.0, 0.5, 0.0 };
	float orangePlus[3] = { 1.0, 0.6, 0.2 };
	float black[3] = { 0.0, 0.0, 0 };
	float pink[3] = { 1.0, 0.5, 0.5 };
	float white[3] = { 1.0, 1.0, 1.0 };

	cout << "initializing Robot L-System" << endl;
	morphFitness = 0;
	for (int i = 0; i < lGenome->amountStates; i++) {
		lGenome->lParameters.push_back(shared_ptr<LPARAMETERS>());
		vector<float>tempVector;
		//	cout << "Initializing state modules" << endl; 
		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = pink[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = green[j];
			}
		case 5:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = orange[j];
			}
		default:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->color[j] = white[j];
			}
			break;
		}

		if (i == 0) {
			modules.push_back(mf->createModuleGenome(10, settings, randomNum));
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			/*	lGenome->lParameters[i]->childConfigurations.push_back(2);
			lGenome->lParameters[i]->childSites.push_back(1);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			/*	lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(2);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(3);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(4);
			lGenome->lParameters[i]->childSiteStates.push_back(1);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();*/
		}
		else if (i == 1) {
			modules.push_back(mf->createModuleGenome(10, settings, randomNum));
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(2);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//	lGenome->lParameters[i]->module = lGenome->moduleFactory->createModuleGenome(4, settings, randomNum);
			//	lGenome->lParameters[i]->childConfigurations.push_back(1);
			//	lGenome->lParameters[i]->childSites.push_back(1);
			//	lGenome->lParameters[i]->childSiteStates.push_back(3);
			//	lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 2) {
			modules.push_back(mf->createModuleGenome(10, settings, randomNum));
			//			lGenome->lParameters[i]->childConfigurations.push_back(3);
			//			lGenome->lParameters[i]->childSites.push_back(0);
			//			lGenome->lParameters[i]->childSiteStates.push_back(1);
			//			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			//			lGenome->lParameters[i]->maxChilds = 0;
		}
		else if (i == 3) {
			modules.push_back(mf->createModuleGenome(4, settings, randomNum));
			lGenome->lParameters[i]->childConfigurations.push_back(0);
			lGenome->lParameters[i]->childSites.push_back(0);
			lGenome->lParameters[i]->childSiteStates.push_back(3);
			lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}
		else if (i == 4) {
			modules.push_back(mf->createModuleGenome(4, settings, randomNum));
		}
		else {
			modules.push_back(mf->createModuleGenome(4, settings, randomNum));
		}
		lGenome->lParameters[i]->currentState = i;
		modules[i]->moduleColor[0] = lGenome->lParameters[i]->color[0];
		modules[i]->moduleColor[1] = lGenome->lParameters[i]->color[1];
		modules[i]->moduleColor[2] = lGenome->lParameters[i]->color[2];

		//	lGenome->mutationRate = 0;
		/*	if (i == 2) {
		lGenome->lParameters[i]->module->state = i;
		lGenome->lParameters[i]->childConfigurations.push_back(0);
		lGenome->lParameters[i]->childSites.push_back(1);
		lGenome->lParameters[i]->childSiteStates.push_back(0);
		lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
		}*/
	}
	//	mutateERLGenome(0.05);
	//	mutateControlERLGenome(0.3);
	mf.reset();
}




int ER_LSystem::initializeLSystem(int amountIncrement, float initialPosition[3]) {
	//	simSetInt32Parameter(sim_intparam_dynamic_step_divider, 25);
	//	getEnvironmentObjects();
	shared_ptr<ModuleFactory> mf = shared_ptr<ModuleFactory>(new ModuleFactory);

	createdModules.clear();
	for (int i = 0; i <= amountIncrement; i++) { // <= !!
		if (createdModules.size() == 0) {
			//	cout << "Module size = 0" << endl; 
			createdModules.push_back(mf->copyModuleGenome(modules[0]));
			int parentHandle = -1;
			vector<float> configuration;
			configuration.resize(6);
			configuration[0] = initialPosition[0];
			configuration[1] = initialPosition[1];
			configuration[2] = initialPosition[2];
			configuration[3] = 0;
			configuration[4] = 0;
			configuration[5] = 0;
			createdModules[0]->createModule(configuration, -1, parentHandle);
			createdModules[0]->parent = -1;
			createdModules[0]->battery = true; // temp
			// axiom is created

		//	int firstObject = createFirstObject(initialPosition, lGenome->lParameters[0].stateType, lGenome->dynamic);
		}
		else {
			//		cout << "INCREMENTING" << endl; 
			incrementLSystem();
		}
	}
	if (createdModules[0]->type != 8) {
		Development::shiftRobotPosition();
	}
	//	float pos[3];
	//	simGetObjectPosition(createdModules[0]->objectHandles[0], -1, pos);
	//	cout << pos[0] << "," << pos[1] << "," << pos[2] << endl;

	if (settings->evolutionType == settings->EMBODIED_EVOLUTION) {
		// set module IDs so they can be controlled
		int m_ID = 1;
		for (int i = 0; i < createdModules.size(); i++) {
			if (createdModules[i]->type == 4 || createdModules[i]->type == 10) {
				createdModules[i]->moduleID = m_ID;
				m_ID++;
			}
		}
	}

	mf.reset();
	return 1;
}


void ER_LSystem::init_noMorph() {

}

void ER_LSystem::setPhenValue() {
	float val = 0.0;
	for (int i = 0; i < createdModules.size(); i++) {
		float pos[3];
		//	cout << "phenValNOW = " << createdModules[i]->phenV << endl;
		val += createdModules[i]->phenV;
		//		simGetObjectPosition(createdModules[i]->phenV), -1, pos);
		//		val += pos[0];
		//		val += pos[1];
		//		val += pos[2];
			//	cout << "val: " << val <<  endl;
	}
	phenValue = val;
}

void ER_LSystem::initCustomMorphology() {
	initializeGenomeCustom(0);
	float position[3] = { 0, 0, 0.1 };
	initializeLSystem(settings->lIncrements, position); // amount increment is not in genome anymore
}


void ER_LSystem::updateColors() {
	for (int i = 0; i < createdModules.size(); i++) {
		float alpha = createdModules[0]->energy;
		if (alpha > 1.0) {
			alpha = 1.0;
		}
		else if (alpha < 0.4) {
			alpha = 0.4;
		}
		// cout << "alpha = " << alpha << endl;
		// cout << "color: " << lGenome->lParameters[createdModules[i]->state]->color[0] << "," << lGenome->lParameters[createdModules[i]->state]->color[1]
		// << "," << lGenome->lParameters[createdModules[i]->state]->color[2] << endl;
		createdModules[i]->colorModule(lGenome->lParameters[createdModules[i]->state]->color, alpha);
	}
}

void ER_LSystem::update() {
	vector<float> input;
	if (settings->environmentType == settings->ENV_SWITCHOBJECTIVE) {
		if (simGetSimulationTime() >= 15) {
			if (incrementer == false) {
				incrementLSystem();
				incrementer = true;
			}
		}
	}
	for (int i = 0; i < createdModules.size(); i++) {
		//float outputModule = 
		vector<float> moduleInput;
		if (settings->controlType == settings->ANN_DEFAULT || settings->ANN_CUSTOM) {
			createdModules[i]->updateModule(input);
			moduleInput.push_back(0.0);
		}
		if (settings->controlType == settings->ANN_DISTRIBUTED_UP
			|| settings->controlType == settings->ANN_DISTRIBUTED_DOWN
			|| settings->controlType == settings->ANN_DISTRIBUTED_BOTH) {
			moduleInput = createdModules[i]->updateModule(input);
		}
		if (settings->controlType == settings->ANN_DISTRIBUTED_UP) {
			if (createdModules[i]->parentModulePointer) { // if a parent pointer is stored
				int parent = createdModules[i]->parent;
				createdModules[parent]->addInput(moduleInput);
				//	createdModules[i]->addInput(createdModules[parent]->moduleOutput);
			}
		}
		else if (settings->controlType == settings->ANN_DISTRIBUTED_DOWN) {
			if (createdModules[i]->parentModulePointer) { // if a parent pointer is stored
				int parent = createdModules[i]->parent;
				createdModules[i]->addInput(createdModules[parent]->moduleOutput);
			}
		}
		else if (settings->controlType == settings->ANN_DISTRIBUTED_BOTH) {
			if (createdModules[i]->parentModulePointer) { // if a parent pointer is stored
				int parent = createdModules[i]->parent;
				createdModules[parent]->addInput(moduleInput);
				createdModules[i]->addInput(createdModules[parent]->moduleOutput);
			}
		}

	}
	if (createdModules.size() < 2) {
		simStopSimulation();
	}
	//updateColors();
	checkForceSensors();
}

void ER_LSystem::getEnvironmentObjects()
{
	settings->envObjectHandles.clear();
	for (int i = 0; i < 20; i++) {
		int envHandle = simGetObjectHandle("col" + i);
		if (envHandle != -1) {
			settings->envObjectHandles.push_back(envHandle);
		}
		else {
			cout << "found " << settings->envObjectHandles.size() << " environment handles" << endl;
			break;
		}
	}
}

void ER_LSystem::setColors() {
	for (int i = 0; i < lGenome->amountStates; i++) {
		float red[3] = { 1.0, 0, 0 };
		float blue[3] = { 0.0, 0.0, 1.0 };
		float yellow[3] = { 1.0, 1.0, 0.0 };
		float green[3] = { 0.0, 0.3, 0.0 };
		float orange[3] = { 1.0, 0.5, 0.0 };
		float orangePlus[3] = { 1.0, 0.6, 0.2 };
		float black[3] = { 0.0, 0.0, 0 };

		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->rgb[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->rgb[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->rgb[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->rgb[j] = green[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->rgb[j] = orange[j];
			}
			break;
		case 5:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->rgb[j] = orangePlus[j];
			}
			break;
		default:
			for (int j = 0; j < 3; j++) {
				lGenome->lParameters[i]->rgb[j] = black[j];
			}
			break;
		}
	}
}

void ER_LSystem::create() {
	cout << "creating" << endl;
	setColors();
	//init(); 

	initializeLSystem(settings->lIncrements, positionFirstObject); // amount increment is not in genome anymore
	// checkJointModule(); // quits simulator when no joint found.
}


int ER_LSystem::getMainHandle() {
	if (createdModules.size() > 0) {
		return createdModules[0]->objectHandles[1];
	}
	else {
		cout << "ERROR: No module could be created, check initial position of the first module." << endl;
		return -1;
	}
}

int ER_LSystem::getAmountBrokenModules() {
	int amountBrokenModules = 0;
	for (int i = 0; i < createdModules.size(); i++) {
		if (createdModules[i]->broken == true) {
			amountBrokenModules++;
		}
	}
	return amountBrokenModules;
}

void ER_LSystem::cubeDrawing(vector<vector<float>> rotatedPoints, float color[3]) {
	int cubeSegment = simAddDrawingObject(sim_drawing_lines + sim_drawing_cyclic, 4, 0.0, -1, 12, color, NULL, NULL, color);
	debugDrawings.push_back(cubeSegment);

	float lineSegment1[6] = { rotatedPoints[0][0], rotatedPoints[0][1], rotatedPoints[0][2], rotatedPoints[1][0], rotatedPoints[1][1], rotatedPoints[1][2] };
	float lineSegment2[6] = { rotatedPoints[1][0], rotatedPoints[1][1], rotatedPoints[1][2], rotatedPoints[2][0], rotatedPoints[2][1], rotatedPoints[2][2] };
	float lineSegment3[6] = { rotatedPoints[2][0], rotatedPoints[2][1], rotatedPoints[2][2], rotatedPoints[3][0], rotatedPoints[3][1], rotatedPoints[3][2] };
	float lineSegment4[6] = { rotatedPoints[3][0], rotatedPoints[3][1], rotatedPoints[3][2], rotatedPoints[0][0], rotatedPoints[0][1], rotatedPoints[0][2] };
	float lineSegment5[6] = { rotatedPoints[0][0], rotatedPoints[0][1], rotatedPoints[0][2], rotatedPoints[4][0], rotatedPoints[4][1], rotatedPoints[4][2] };
	float lineSegment6[6] = { rotatedPoints[1][0], rotatedPoints[1][1], rotatedPoints[1][2], rotatedPoints[5][0], rotatedPoints[5][1], rotatedPoints[5][2] };
	float lineSegment7[6] = { rotatedPoints[2][0], rotatedPoints[2][1], rotatedPoints[2][2], rotatedPoints[6][0], rotatedPoints[6][1], rotatedPoints[6][2] };
	float lineSegment8[6] = { rotatedPoints[3][0], rotatedPoints[3][1], rotatedPoints[3][2], rotatedPoints[7][0], rotatedPoints[7][1], rotatedPoints[7][2] };
	float lineSegment9[6] = { rotatedPoints[4][0], rotatedPoints[4][1], rotatedPoints[4][2], rotatedPoints[5][0], rotatedPoints[5][1], rotatedPoints[5][2] };
	float lineSegment10[6] = { rotatedPoints[5][0], rotatedPoints[5][1], rotatedPoints[5][2], rotatedPoints[6][0], rotatedPoints[6][1], rotatedPoints[6][2] };
	float lineSegment11[6] = { rotatedPoints[6][0], rotatedPoints[6][1], rotatedPoints[6][2], rotatedPoints[7][0], rotatedPoints[7][1], rotatedPoints[7][2] };
	float lineSegment12[6] = { rotatedPoints[7][0], rotatedPoints[7][1], rotatedPoints[7][2], rotatedPoints[4][0], rotatedPoints[4][1], rotatedPoints[4][2] };

	simAddDrawingObjectItem(cubeSegment, lineSegment1);
	simAddDrawingObjectItem(cubeSegment, lineSegment2);
	simAddDrawingObjectItem(cubeSegment, lineSegment3);
	simAddDrawingObjectItem(cubeSegment, lineSegment4);
	simAddDrawingObjectItem(cubeSegment, lineSegment5);
	simAddDrawingObjectItem(cubeSegment, lineSegment6);
	simAddDrawingObjectItem(cubeSegment, lineSegment7);
	simAddDrawingObjectItem(cubeSegment, lineSegment8);
	simAddDrawingObjectItem(cubeSegment, lineSegment9);
	simAddDrawingObjectItem(cubeSegment, lineSegment10);
	simAddDrawingObjectItem(cubeSegment, lineSegment11);
	simAddDrawingObjectItem(cubeSegment, lineSegment12);

}

float ER_LSystem::checkArea(float interSection[3], float pps[4][3]) {

	float alphaD = sqrt(powf((pps[0][0] - pps[1][0]), 2) + powf((pps[0][1] - pps[1][1]), 2) + powf((pps[0][2] - pps[1][2]), 2));
	float betaD = sqrt(powf((pps[0][0] - pps[2][0]), 2) + powf((pps[0][1] - pps[2][1]), 2) + powf((pps[0][2] - pps[2][2]), 2));
	//	cout << "alpha and beta should be the same:" << endl;
	//	cout << "alphaD = " << alphaD << endl;
	//	cout << "betaD = " << betaD << endl;
	float areaX = alphaD * betaD;

	float tLine1 = sqrt(powf((pps[0][0] - interSection[0]), 2) + powf((pps[0][1] - interSection[1]), 2) + powf((pps[0][2] - interSection[2]), 2));
	float tLine2 = sqrt(powf((pps[1][0] - interSection[0]), 2) + powf((pps[1][1] - interSection[1]), 2) + powf((pps[1][2] - interSection[2]), 2));
	float tLine3 = sqrt(powf((pps[2][0] - interSection[0]), 2) + powf((pps[2][1] - interSection[1]), 2) + powf((pps[2][2] - interSection[2]), 2));
	float tLine4 = sqrt(powf((pps[3][0] - interSection[0]), 2) + powf((pps[3][1] - interSection[1]), 2) + powf((pps[3][2] - interSection[2]), 2));

	float area1 = 0.5 * tLine1 * tLine2;
	float area2 = 0.5 * tLine2 * tLine3;
	float area3 = 0.5 * tLine3 * tLine4;
	float area4 = 0.5 * tLine4 * tLine1;
	//	cout << "interSection Point = " << interSection[0] << ", " << interSection[1] << ", " << interSection[2] << endl;
	//	cout << "triangle areas are: " << area1 << ", " << area2 << ", " << area3 << ", " << area4 << endl;
	float areaBound = area1 + area2 + area3 + area4;

	//	cout << "areas are: " << endl;
	//	cout << "	areaX = " << areaX << endl;
	//	cout << "	areaBound =" << areaBound << endl;
	return (1 / areaX * areaBound);
}



bool ER_LSystem::checkCollisionBasedOnRotatedPoints(int objectHandle) {
	float objectOrigin[3];
	simGetObjectPosition(objectHandle, -1, objectOrigin);
	float size[3];
	float rotationOrigin[3] = { 0,0,0 };
	simGetObjectFloatParameter(objectHandle, 18, &size[0]);
	simGetObjectFloatParameter(objectHandle, 19, &size[1]);
	simGetObjectFloatParameter(objectHandle, 20, &size[2]);
	for (int i = 0; i < 3; i++) {
		size[i] = size[i] * 2;
	}

	vector<vector<float>> cubeVertex; // 8 points in 3d space
	vector<vector<float>> points;
	points.resize(8);

	float objectMatrix[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

	simGetObjectMatrix(objectHandle, -1, objectMatrix);
	//for (int i = 0; i < 12; i++) {
	//	cout << objectMatrix[i] << ", ";
	//} cout << endl;

	points[0].push_back(rotationOrigin[0] + (0.5 * size[0]));
	points[0].push_back(rotationOrigin[1] + (0.5 * size[1]));
	points[0].push_back(rotationOrigin[2] + (0.5 * size[2]));

	points[1].push_back(rotationOrigin[0] - (0.5 * size[0]));
	points[1].push_back(rotationOrigin[1] + (0.5 * size[1]));
	points[1].push_back(rotationOrigin[2] + (0.5 * size[2]));

	points[2].push_back(rotationOrigin[0] - (0.5 * size[0]));
	points[2].push_back(rotationOrigin[1] - (0.5 * size[1]));
	points[2].push_back(rotationOrigin[2] + (0.5 * size[2]));

	points[3].push_back(rotationOrigin[0] + (0.5 * size[0]));
	points[3].push_back(rotationOrigin[1] - (0.5 * size[1]));
	points[3].push_back(rotationOrigin[2] + (0.5 * size[2]));

	points[4].push_back(rotationOrigin[0] + (0.5 * size[0]));
	points[4].push_back(rotationOrigin[1] + (0.5 * size[1]));
	points[4].push_back(rotationOrigin[2] - (0.5 * size[2]));

	points[5].push_back(rotationOrigin[0] - (0.5 * size[0]));
	points[5].push_back(rotationOrigin[1] + (0.5 * size[1]));
	points[5].push_back(rotationOrigin[2] - (0.5 * size[2]));

	points[6].push_back(rotationOrigin[0] - (0.5 * size[0]));
	points[6].push_back(rotationOrigin[1] - (0.5 * size[1]));
	points[6].push_back(rotationOrigin[2] - (0.5 * size[2]));

	points[7].push_back(rotationOrigin[0] + (0.5 * size[0]));
	points[7].push_back(rotationOrigin[1] - (0.5 * size[1]));
	points[7].push_back(rotationOrigin[2] - (0.5 * size[2]));

	vector<vector<float>> rotatedPoints;
	rotatedPoints.resize(8);
	for (int i = 0; i < 8; i++) {
		rotatedPoints[i].push_back((points[i][0] * objectMatrix[0]) + (points[i][1] * objectMatrix[1]) + (points[i][2] * objectMatrix[2]));
		rotatedPoints[i].push_back((points[i][0] * objectMatrix[4]) + (points[i][1] * objectMatrix[5]) + (points[i][2] * objectMatrix[6]));
		rotatedPoints[i].push_back((points[i][0] * objectMatrix[8]) + (points[i][1] * objectMatrix[9]) + (points[i][2] * objectMatrix[10]));
		rotatedPoints[i][0] += objectOrigin[0];
		rotatedPoints[i][1] += objectOrigin[1];
		rotatedPoints[i][2] += objectOrigin[2];
		if (rotatedPoints[i][2] < minimumHeight) {
			return true;
		}
	}
	return false;
}

void ER_LSystem::symmetryMutation(float mutationRate) {
	return;
	for (int i = 0; i < lGenome->lParameters.size(); i++) {
		if (randomNum->randFloat(0.0, 1.0) < mutationRate) {
			int amountChilds = lGenome->lParameters[i]->childSites.size();
			if (amountChilds != 0) {
				int chosenOne = randomNum->randInt(amountChilds, 0);
				int mirrorType = randomNum->randInt(3, 0);
				vector<int> mirrorSite = modules[i]->getMirrorSite(lGenome->lParameters[i]->childSites[chosenOne], lGenome->lParameters[i]->childConfigurations[chosenOne], mirrorType);
				int chosenSite = lGenome->lParameters[i]->childSites[chosenOne];
				int chosenCon = lGenome->lParameters[i]->childConfigurations[chosenOne];
				int chosenState = lGenome->lParameters[i]->childSiteStates[chosenOne];
				int newPos = randomNum->randInt(getMaxChilds(lGenome->lParameters[i]->type), 0);

				if (newPos >= amountChilds) {
					lGenome->lParameters[i]->childSites.push_back(mirrorSite[0]);
					lGenome->lParameters[i]->childConfigurations.push_back(mirrorSite[1]);
					lGenome->lParameters[i]->childSiteStates.push_back(lGenome->lParameters[i]->childSiteStates[chosenOne]);
				}
				else {
					lGenome->lParameters[i]->childSites[newPos] = mirrorSite[0];
					lGenome->lParameters[i]->childConfigurations[newPos] = mirrorSite[1];
					lGenome->lParameters[i]->childSiteStates[newPos] = lGenome->lParameters[i]->childSiteStates[chosenOne];
				}
				lGenome->lParameters[i]->amountChilds = lGenome->lParameters[i]->childSites.size();
			}
		}
	}
	cout << "Done with symmetry mutation" << endl;
}