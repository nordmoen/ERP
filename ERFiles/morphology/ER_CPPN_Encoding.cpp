#include "ER_CPPN_Encoding.h"
#include <iostream>
#include <sstream>
#include <cmath>


ER_CPPN_Encoding::ER_CPPN_Encoding()
{
	modular = true;
}


ER_CPPN_Encoding::~ER_CPPN_Encoding()
{
	
}

void ER_CPPN_Encoding::init() {
	genome = shared_ptr<GENOTYPE>(new GENOTYPE);
	maxModuleTypes = settings->maxModuleTypes;
	if (settings->evolutionType != settings->EMBODIED_EVOLUTION && settings->morphologyType != settings->QUADRUPED_DIRECT) {
		initializeGenome(0);
	}
	else if (settings->morphologyType == settings->QUADRUPED_DIRECT) {
		// not used in CPPN
		cout << "CPPN encoding cannot yet create a quadruped" << endl;
	}
	
}

int ER_CPPN_Encoding::initializeGenome(int type) {
	//first read settings

	if (settings->verbose) {
		cout << "initializing CPPN Encoding Genome" << endl;
	}
	morphFitness = 0;
	
	// CPPN currently takes the increment and position as inputs
	cppn = shared_ptr<CPPN>(new CPPN);
	cppn->settings = settings;
	cppn->init(8, 8, 6); // output is type, orientation and activation of sin 
	// cppn->mutate(settings->morphMutRate);
	cppn->mutate(0.5);

	// make a temporary storage for phenotype based on genotypic information
	//for (int i = 0; i < genome->amountModules; i++) {
	//	genome->moduleParameters.push_back(shared_ptr<MODULEPARAMETERS>(new MODULEPARAMETERS));
	//	genome->moduleParameters[i]->type = settings->initialModuleType;
	//	vector<float>tempVector;
	//	// currently everything has a neural network...
	//	genome->moduleParameters[i]->control = cf->createNewControlGenome(settings->controlType, settings, randomNum);
	//	if (settings->controlType == settings->ANN_DISTRIBUTED_BOTH) {
	//		genome->moduleParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons); // 2 additional inputs and outputs used fotr 
	//		cout << "initializing both!!!" << endl;
	//		//			cout << "OUTPUTSIZE = " << genome->moduleParameters[i]->control-> outputLayer.size() << endl;

	//	}
	//	else if (settings->controlType == settings->ANN_DISTRIBUTED_UP) {
	//		genome->moduleParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons); // 2 additional inputs and outputs used fotr 
	//	}
	//	else if (settings->controlType == settings->ANN_DISTRIBUTED_DOWN) {
	//		genome->moduleParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons); // 2 additional inputs and outputs used fotr 
	//	}
	//	else {
	//		genome->moduleParameters[i]->control->init(settings->initialInputNeurons, settings->initialInterNeurons, settings->initialOutputNeurons);
	//	}


	//}

	// mutateCPPN(0.5);
	// mutateERGenome(0.5);
	return 1;
}

void ER_CPPN_Encoding::createAtPosition(float x, float y, float z) {
	cout << "x, y, z: " << x << ", " << y << ", " << z << endl;
	float position[3];
	setColors();
	position[0] = x;
	position[1] = y;
	position[2] = z;
	positionFirstObject[0] = x;
	positionFirstObject[1] = y;
	positionFirstObject[2] = z;
	create();
	//	initializeCPPNEncoding(position); // / amount increment is not in genome anymore
}


void ER_CPPN_Encoding::printSome() {
	BaseMorphology::printSome();
	cout << "printing some from ER_CPPN_Interpreter" << endl;
}


void ER_CPPN_Encoding::checkForceSensors() {
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

int ER_CPPN_Encoding::initializeCPPNEncoding(float initialPosition[3]) {
	unique_ptr<ModuleFactory> mf = unique_ptr<ModuleFactory>(new ModuleFactory);
	//	simSetInt32Parameter(sim_intparam_dynamic_step_divider, 25);
	if (settings->verbose) {
		cout << "initializing CPPN encoding interpreter" << endl;
	}
	createdModules.clear();
	for (int i = 1; i < genome->moduleParameters.size(); i++) {
		genome->moduleParameters[i]->expressed = false;
	}
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

	for (int i = 1; i < modules.size(); i++) {
		if (modules[i]->parent == 0) {
			modules[i]->parentModulePointer = createdModules[0];
		}
	}
	for (int i = 0; i < modules.size(); i++) {
		modules[i]->moduleID = i;
	}
	//cout << "looping through modules" << endl;
	for (int i = 1; i < modules.size(); i++) {
		int parentNr = genome->moduleParameters[i]->parent;
		int parentSite = genome->moduleParameters[i]->parentSite;
		int orien = genome->moduleParameters[i]->orientation;
		int createdParentNumber = -1;
		for (int n = 0; n < createdModules.size(); n++)
		{
			if (createdModules[n]->moduleID == parentNr) {
				createdParentNumber = n;
			}
		}
		if (settings->verbose) {
			cout << "i: " << i << endl;
		}
		if (createdModules.size() < settings->maxAmountModules) {
			if (modules[i]->parentModulePointer != NULL && createdParentNumber > -1 && createdModules[createdParentNumber] != NULL) {
				if (genome->moduleParameters[parentNr]->expressed == true) { // Return if the module is not expressed. 
					if (createdModules[createdParentNumber]->siteConfigurations.size() == 0) {
						//	cout << "state " << createdModules[createdParentNumber]->state << ",";
						//	cout << "id " << createdModules[createdParentNumber]->moduleID << ",";
							//	cout << "id " << createdModules[parentNr]-> << endl;
					}
					// parentHandle = createdModules[i]->parentModulePointer->;
					//cout << "should create module : " << i << ",";
					shared_ptr<ER_Module> parentModulePointer = modules[i]->parentModulePointer;
					if (parentModulePointer == NULL) {
						cout << ", null , ";
					}
					//cout << "parentModulePointer = " << parentModulePointer << ", ";
					//cout << "parentSite = " << parentSite << ", ";
					//cout << " .. " << parentModulePointer->moduleID << ",";
					//cout << " pType " << parentModulePointer->type << ",";

					parentHandle = parentModulePointer->siteConfigurations[parentSite][0]->parentHandle;
					int relativePositionHandle = parentModulePointer->siteConfigurations[parentSite][0]->relativePosHandle;
					//cout << " 1 ,";
					createdModules.push_back(mf->copyModuleGenome(modules[i]));
					createdModules[createdModules.size() - 1]->parent = createdParentNumber;
					//createdModules[createdModules.size() - 1]->parentSite = parentSite;
					//cout << " 1.1, ";
					int createdModulesSize = createdModules.size();
					vector<float> siteConfiguration;
					//cout << "pnr:" << createdParentNumber << ", cMs: " << createdModules.size() << ", or " << orien << ",";
					//cout << createdModules[createdParentNumber]->type << ",";
					//cout << "sc.size: " << createdModules[createdParentNumber]->siteConfigurations.size() << ",";
					//cout << "orien = " << orien << ",";
					//cout << "parentSite = " << parentSite << ",";

					//if (createdModules[createdParentNumber]->siteConfigurations.size() < 1) {
					//	cout << "ERROR" << endl;
					//}
					siteConfiguration.push_back(createdModules[createdParentNumber]->siteConfigurations[parentSite][orien]->x);
					siteConfiguration.push_back(createdModules[createdParentNumber]->siteConfigurations[parentSite][orien]->y);
					siteConfiguration.push_back(createdModules[createdParentNumber]->siteConfigurations[parentSite][orien]->z);
					siteConfiguration.push_back(createdModules[createdParentNumber]->siteConfigurations[parentSite][orien]->rX);
					siteConfiguration.push_back(createdModules[createdParentNumber]->siteConfigurations[parentSite][orien]->rY);
					siteConfiguration.push_back(createdModules[createdParentNumber]->siteConfigurations[parentSite][orien]->rZ);
					//cout << " a ,";
					createdModules[createdModulesSize - 1]->createModule(siteConfiguration, relativePositionHandle, parentHandle);
					createdModulesSize = createdModules.size();
					//cout << " b ,";

					// set color
					// createdModules[createdModulesSize - 1]->colorModule(genome->moduleParameters[i]->color, 1.0);

					vector<int> exception;
					exception.push_back(parentHandle);
					for (int p = 0; p < createdModules[createdModulesSize - 1]->objectHandles.size(); p++) {
						exception.push_back(createdModules[createdModulesSize - 1]->objectHandles[p]);
					}

					if (checkLCollisions(createdModules[createdModulesSize - 1], exception) == true) {
						createdModules.erase(createdModules.begin() + (createdModulesSize - 1));
						//		genome->moduleParameters[i]->expressed = false;
					}
					else {
						for (int n = 0; n < modules.size(); n++) {
							if (modules[n]->parent == i) {
								modules[n]->parentModulePointer = createdModules[createdModulesSize - 1];
							}
						}
						genome->moduleParameters[i]->expressed = true;
					}
					//cout << "created Module" << endl;
				}
			}
		}
		else {
			for (int j = 0; j < genome->moduleParameters.size(); j++) {
				//	cout << "pi: " << genome->moduleParameters[j]->parent << endl;
			}
			// cout << "ERROR: " << "No parent Module Pointer or module not actually created" << endl;
		}
	}
	if (settings->verbose) {
		cout << "shifting robot position" << endl;
	}
	if (createdModules[0]->type != 8) {
		Development::shiftRobotPosition();
	}
	//	float pos[3];
	//	simGetObjectPosition(createdModules[0]->objectHandles[0], -1, pos);
	//	cout << pos[0] << "," << pos[1] << "," << pos[2] << endl;
	//	update();
	mf.reset();
	return 1;
}

void ER_CPPN_Encoding::mutate() {
	mutateCPPN(settings->morphMutRate);
}


int ER_CPPN_Encoding::mutateCPPN(float mutationRate) {
	if (settings->verbose) {
		cout << "mutating CPPN" << endl;
	}
	cppn->mutate(settings->morphMutRate);

	if (settings->verbose) {
		cout << "mutated CPPN" << endl;
	}
	return 1;
}


void ER_CPPN_Encoding::crossover(shared_ptr<Morphology> partnerMorph, float cr) {
		
	shared_ptr<ER_CPPN_Encoding>morpho(static_pointer_cast<ER_CPPN_Encoding>(partnerMorph));   //*partnerMorph(ER_CPPN_Encoding()));
	shared_ptr<GENOTYPE> tempGenome;
	tempGenome = morpho->genome->clone(); 

	bool cross = false;
	for (int i = 0; i < genome->amountModules; i++) {
		if (randomNum->randFloat(0, 1) < cr) {
			if (cross == false) {
				cross = true;
			}
			else {
				cross = false;
			}
		}
		if (cross == true) {
			// do some sort of crossover here
		}
	}
}


void ER_CPPN_Encoding::initializeQuadruped(int type)
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
	cf.reset();
}

const std::string ER_CPPN_Encoding::generateGenome(int indNum, float fitness) const {
	if (settings->verbose) {
		cout << "generating CPPN genome " << endl << "-------------------------------- " << endl;
	}

	int amountStates = genome->moduleParameters.size();
	stringstream cppndata = cppn->getControlParams();
	
	ostringstream genomeText;
	genomeText << "#CPPN Genome" << endl;
	genomeText << "#Individual:" << indNum << "," << endl;
	genomeText << "#Fitness:," << fitness << "," << endl;
	genomeText << "#phenValue;," << phenValue << endl;
	genomeText << "#AmountStates:," << amountStates << "," << endl << endl;
	
	genomeText << "#CPPN_Start," << endl;
	genomeText << cppndata.str() << endl;
	genomeText << "#CPPN_End," << endl;
	genomeText << endl;

	return genomeText.str();
}

float ER_CPPN_Encoding::getFitness() {
	return fitness;
}

bool ER_CPPN_Encoding::loadGenome(std::istream &genomeInput, int individualNumber)
{
	if (settings->verbose) {
		cout << "loading genome " << individualNumber << "(ER_CPPN_Encoding)" << endl;
	}
	genome = std::shared_ptr<GENOTYPE>(new GENOTYPE);
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
	vector<string> cppnValues;
	bool checkingModule = false;
	bool checkingControl = false;
	bool checkingCPPN = false;


	list<string>::const_iterator it = values.begin();
	for (it = values.begin(); it != values.end(); it++) {
		string tmp = *it;
		if (settings->verbose) {
			cout << "," << tmp;
		}
		if (checkingModule == true) {
			moduleValues.push_back(tmp);
		}
		if (checkingControl == true) {
			controlValues.push_back(tmp);
		}
		if (checkingCPPN == true) {
			cppnValues.push_back(tmp);
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
			genome->amountModules = atoi(tmp.c_str());
			for (int i = 0; i < genome->amountModules; i++) {
				genome->moduleParameters.push_back(shared_ptr<MODULEPARAMETERS>(new MODULEPARAMETERS));
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
			genome->moduleParameters[moduleNum]->childSiteStates.resize(ac);
		}
		else if (tmp == "#ModuleParent:")
		{
			it++;
			tmp = *it;
			genome->moduleParameters[moduleNum]->parent = atoi(tmp.c_str());
		}
		else if (tmp == "#ModuleType:")
		{
			it++;
			tmp = *it;
			genome->moduleParameters[moduleNum]->type = atoi(tmp.c_str());
		}
		else if (tmp == "#ParentSite:")
		{
			it++;
			tmp = *it;
			genome->moduleParameters[moduleNum]->parentSite = atoi(tmp.c_str());
		}
		else if (tmp == "#ParentSiteOrientation:")
		{
			genome->moduleParameters[moduleNum]->orientation = atoi(tmp.c_str());
		}
		else if (tmp == "#ModuleType:") {
			it++;
			tmp = *it;
			//		cout << "creating module of type: " << atoi(tmp.c_str()) << endl; 
			genome->moduleParameters[moduleNum]->type = atoi(tmp.c_str());
			//		cout << "state = " << lGenome->lParameters[moduleNum].module->state << endl;
		}
		if (tmp == "#CPPN_Start") {
			checkingCPPN = true;
		}
		else if (tmp == "#CPPN_End") {
			checkingCPPN = false;
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
				genome->moduleParameters[moduleNum]->control = controlFactory->createNewControlGenome(atoi(controlValues[2].c_str()), settings, randomNum); // 0 is ANN
			//	lGenome->lParameters[moduleNum]->control->init(1, 2, 1);
				genome->moduleParameters[moduleNum]->control->setControlParams(controlValues);
				checkingControl = false;
				controlValues.clear();
				controlFactory.reset();
			}
			moduleNum++;
			checkingModule = false;
		}
	}

	cppn = shared_ptr<Control>(new CPPN);
	cppn->settings = settings;
	cppn->setControlParams(cppnValues);

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
	for (int i = 0; i < genome->amountModules; i++) {
		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->color[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->color[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->color[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->color[j] = pink[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->color[j] = red[j];
			}
			break;
		case 5:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->color[j] = yellow[j];
			}
			break;
		default:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->color[j] = grey[j];
			}
			break;
		}
		genome->moduleParameters[i]->moduleColor[0] = genome->moduleParameters[i]->color[0];
		genome->moduleParameters[i]->moduleColor[1] = genome->moduleParameters[i]->color[1];
		genome->moduleParameters[i]->moduleColor[2] = genome->moduleParameters[i]->color[2];
	}

	if (settings->verbose) {
		cout << "loaded cppn genome" << endl;
	}
	return true;
}

shared_ptr<Morphology> ER_CPPN_Encoding::clone() const {
	BaseMorphology::clone();
	shared_ptr<ER_CPPN_Encoding> ur = make_unique<ER_CPPN_Encoding>(*this);
	ur->genome = this->genome->clone();
	for (int i = 0; i < ur->genome->moduleParameters.size(); i++) {
		ur->genome->moduleParameters[i] = this->genome->moduleParameters[i]->clone();
	}
	ur->cppn = this->cppn->clone();
	//make_unique<CPPN>(this)
	//shared_ptr<CPPN> cppnClone = make_unique<CPPN>(*cppn);
//	cppnClone->makeDependenciesUnique();
//	ur->cppn = cppnClone->clone();
	return ur;
}

void ER_CPPN_Encoding::symmetryMutation(float mutationRate) {
	cout << "This version does not support symmetry mutation, check code" << endl;
}

int ER_CPPN_Encoding::mutateControlERGenome(float mutationRate) {
	cout << "mutating l-genome" << endl;
	for (int i = 0; i < genome->moduleParameters.size(); i++) {
		//		cout << "i = " << i << endl; 
		genome->moduleParameters[i]->control->mutate(mutationRate);
	}
	return 1;
}

void ER_CPPN_Encoding::deleteModuleFromGenome(int num)
{
	while (genome->moduleParameters[num]->childSiteStates.size() > 0) {
		deleteModuleFromGenome(genome->moduleParameters[num]->childSiteStates.size() - 1);
		genome->moduleParameters[num]->childSiteStates.pop_back();
	}
}

void ER_CPPN_Encoding::checkGenome(int individualNumber, int sceneNum) {
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

void ER_CPPN_Encoding::checkControl(int individual, int sceneNum) {
	checkGenome(individual, sceneNum);
}

void ER_CPPN_Encoding::setPhenValue() {
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

void ER_CPPN_Encoding::create() {
	if (genome == NULL) {
		// only initialize when this hasn't been done already
		init();
	}
	// from the CPPN create a robot
	if (settings->verbose) {
		cout << "creating CPPN robot" << endl;
	}
	unique_ptr<ModuleFactory> mf = unique_ptr<ModuleFactory>(new ModuleFactory);
	unique_ptr<ControlFactory> cf = unique_ptr<ControlFactory>(new ControlFactory);
	genome->moduleParameters.clear();
	int moduleAmount = settings->moduleTypes.size();
	// create axiom module
	genome->moduleParameters.push_back(shared_ptr<MODULEPARAMETERS>(new MODULEPARAMETERS));
	genome->moduleParameters[0]->type = settings->initialModuleType;
	genome->moduleParameters[0]->maxChilds = 5;
	genome->moduleParameters[0]->parent = -1;
	genome->moduleParameters[0]->parentSite = -1;
	genome->moduleParameters[0]->orientation = 0;
	// create axiom module control which is actually not used... 
	genome->moduleParameters[0]->control = cf->createNewControlGenome(settings->controlType, settings, randomNum);
	genome->moduleParameters[0]->control->init(1, 1, 1);
	if (settings->verbose) {
		cout << "quereuing cppn" << endl;
	}
	for (int i = 0; i < maxIterations; i++)
	{
		// query CPPN a few times. 
		if (settings->verbose) {
			cout << "query: " << i << endl;
		}
		int sizeIt = genome->moduleParameters.size();
		for (int n = 0; n < sizeIt; n++) {
			if (genome->moduleParameters[n]->queried == false) {
				genome->moduleParameters[n]->queried = true;
				for (int m = 0; m < genome->moduleParameters[n]->maxChilds; m++) {
					vector<float> inputs;
					inputs.push_back(genome->moduleParameters[n]->type / 10);
					if (genome->moduleParameters[n]->orientation < 0.5) {
						inputs.push_back(1);
						inputs.push_back(0);
						inputs.push_back(0);
						inputs.push_back(0);
					}
					else if (genome->moduleParameters[n]->orientation < 1.5) {
						inputs.push_back(0);
						inputs.push_back(1);
						inputs.push_back(0);
						inputs.push_back(0);
					}
					else if (genome->moduleParameters[n]->orientation < 2.5) {
						inputs.push_back(0);
						inputs.push_back(0);
						inputs.push_back(1);
						inputs.push_back(0);
					}
					else {
						inputs.push_back(0);
						inputs.push_back(0);
						inputs.push_back(0);
						inputs.push_back(1);
					}
					inputs.push_back(genome->moduleParameters[n]->orientation / 4);
					inputs.push_back(genome->moduleParameters[n]->parentSite / genome->moduleParameters[n]->maxChilds);
					inputs.push_back(i / maxIterations);
					// cout << "updating cppn" << endl;
					vector<float> moduleTypeFloat = cppn->update(inputs);
					// cout << "cppn updated" << endl;
					if (moduleTypeFloat[5] > 0.5) {
						// only create module if output is above certain threshold
						int typeM = (int)moduleTypeFloat[0] * (moduleAmount - 1);
						if (typeM < 0) {
							typeM = 0;
						}
						// cout << "typeM:  " << typeM << endl;
						int mt = settings->moduleTypes[typeM];
						genome->moduleParameters.push_back(shared_ptr<MODULEPARAMETERS>(new MODULEPARAMETERS));
						genome->moduleParameters[genome->moduleParameters.size() - 1]->type = mt;
						// genome->moduleParameters[n]->childSiteStates[m] = settings->moduleTypes[(int)((moduleAmount + 1) * moduleTypeFloat[0]) - (1.0 / (moduleAmount + 1))];
						int mn = genome->moduleParameters.size() - 1;
						if (settings->moduleTypes[typeM] != 17) {
							genome->moduleParameters[mn]->maxChilds = getMaxChilds(settings->moduleTypes[typeM]);
						}

						// genome->moduleParameters[mn]->currentState = n;
						genome->moduleParameters[mn]->parent = n;
						genome->moduleParameters[mn]->parentSite = m;
						int ori = (int)(floor(moduleTypeFloat[1] * 3.99));
						if (ori < 0) {
							ori = 0;
						}
						// cout << "ORI:" << ori << endl;
						genome->moduleParameters[mn]->orientation = ori;
						genome->moduleParameters[mn]->control = cf->createNewControlGenome(1, settings, randomNum);
						genome->moduleParameters[mn]->control->init(1, 1, 1);
						vector<float> controlValues;
						controlValues.push_back(moduleTypeFloat[2]);
						controlValues.push_back(moduleTypeFloat[3]);
						controlValues.push_back(moduleTypeFloat[4]);
						genome->moduleParameters[mn]->control->setFloatParameters(controlValues);
					}
				}
			}
		}

	}
	if (settings->verbose) {
		cout << "Done querying" << endl;
	}
	cf.reset();
	setColors();
	modules.clear();

	for (int i = 0; i < genome->moduleParameters.size(); i++) {
		modules.push_back(mf->createModuleGenome(genome->moduleParameters[i]->type, settings, randomNum));
		modules[i]->state = i;
		modules[i]->type = genome->moduleParameters[i]->type;
		modules[i]->control = genome->moduleParameters[i]->control;
		modules[i]->parent = genome->moduleParameters[i]->parent;
		modules[i]->parentSite = genome->moduleParameters[i]->parentSite;
		modules[i]->orientation = genome->moduleParameters[i]->orientation;
	}
	mf.reset();
	initializeCPPNEncoding(positionFirstObject); // amount increment is not in genome anymore
	checkJointModule(); // quits simulator when no joint found. 
}


void ER_CPPN_Encoding::update() {
	vector<float> input;
	for (int i = 0; i < createdModules.size(); i++) {
		//float outputModule = 
		vector<float> moduleInput;
		if (settings->controlType == settings->ANN_CUSTOM) {
			createdModules[i]->updateModule(input);
			moduleInput.push_back(0.0);
		}
		if (settings->controlType == settings->ANN_DEFAULT) {
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
				createdModules[i]->parentModulePointer->addInput(moduleInput);
				//	createdModules[i]->addInput(createdModules[parent]->moduleOutput);
			}
		}
		else if (settings->controlType == settings->ANN_DISTRIBUTED_DOWN) {
			if (createdModules[i]->parentModulePointer) { // if a parent pointer is stored
				int parent = createdModules[i]->parent;
				createdModules[i]->addInput(createdModules[i]->parentModulePointer->moduleOutput);
			}
		}
		else if (settings->controlType == settings->ANN_DISTRIBUTED_BOTH) {
			if (createdModules[i]->parentModulePointer) { // if a parent pointer is stored
				//int parent = createdModules[i]->parent;
				createdModules[i]->parentModulePointer->addInput(moduleInput);
				createdModules[i]->addInput(createdModules[i]->parentModulePointer->moduleOutput);
			}
		}

	}
	checkForceSensors();
}

void ER_CPPN_Encoding::updateColors() {
	// not working for direct encoding yet
	for (int i = 0; i < createdModules.size(); i++) {
		float alpha = createdModules[0]->energy;
		if (alpha > 1.0) {
			alpha = 1.0;
		}
		else if (alpha < 0.4) {
			alpha = 0.4;
		}
		//	cout << "alpha = " << alpha << endl;
		createdModules[i]->colorModule(genome->moduleParameters[createdModules[i]->state]->color, alpha);
	}
}

void ER_CPPN_Encoding::setColors() {
	for (int i = 0; i < genome->amountModules; i++) {
		float red[3] = { 1.0, 0, 0 };
		float blue[3] = { 0.0, 0.0, 1.0 };
		float yellow[3] = { 1.0, 1.0, 0.0 };
		float green[3] = { 0.0, 0.3, 0.0 };
		float orange[3] = { 1.0, 0.5, 0.0 };
		float orangePlus[3] = { 1.0, 0.6, 0.2 };
		float black[3] = { 0.0, 0.0, 0 };
		float grey[3] = { 0.45,0.45,0.45 };

		switch (i) {
		case 0:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->rgb[j] = red[j];
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->rgb[j] = blue[j];
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->rgb[j] = yellow[j];
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->rgb[j] = green[j];
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->rgb[j] = orange[j];
			}
			break;
		case 5:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->rgb[j] = orangePlus[j];
			}
			break;
		default:
			for (int j = 0; j < 3; j++) {
				genome->moduleParameters[i]->rgb[j] = grey[j];
			}
			break;
		}
	}
}

int ER_CPPN_Encoding::getMainHandle() {
	if (createdModules.size() > 0) {
		return createdModules[0]->objectHandles[1];
	}
	else {
		cout << "ERROR: No module could be created, check initial position of the first module. " << endl;
	}
}

void ER_CPPN_Encoding::savePhenotype(int ind, float fitness)
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

int ER_CPPN_Encoding::getAmountBrokenModules() {
	int amountBrokenModules = 0;
	for (int i = 0; i < createdModules.size(); i++) {
		if (createdModules[i]->broken == true) {
			amountBrokenModules++;
		}
	}
	return amountBrokenModules;
}

