#pragma once
#include "Settings.h"

/*!
 * The settings that are set in the constructor are mainly for debugging purposes. 
 * 
 */
Settings::Settings() {
	// set default module parameters
	moduleTypes.push_back(1);
	moduleTypes.push_back(4);
	moduleTypes.push_back(4);
	moduleTypes.push_back(4);
	moduleTypes.push_back(4);
	verbose = true;

	for (int i = 0; i < moduleTypes.size(); i++) {
		vector <int> tmpMaxModuleTypes;
		tmpMaxModuleTypes.push_back(moduleTypes[i]);
		tmpMaxModuleTypes.push_back(50);
		maxModuleTypes.push_back(tmpMaxModuleTypes);
	}
	amountModules = moduleTypes.size();
	maxModuleTypes[0][1] = 100; // one base module
	maxAmountModules = 20;
	// morphologyType = CUSTOM_MORPHOLOGY; // MODULAR_DIRECT;
	morphologyType = MODULAR_LSYSTEM;
	populationSize = 20;
	energyDissipationRate = 0.0;
	lIncrements = 4; // not used, should be somewhere else?
//	environmentType = ENV_SWITCHOBJECTIVE;
//	controlType = ANN_DEFAULT;
	verbose = false;
	//verbose = true;
	controlType = ANN_CUSTOM;
	initialInputNeurons = 1;
	initialInterNeurons = 1;
	initialOutputNeurons = 1;
	initialAmountConnectionsNeurons = 1;
	evolutionType = STEADY_STATE;
	seed = 0;
//	instanceType = INSTANCE_REGULAR;
	morphMutRate = 0.1;
	mutationRate = 0.1;
	maxGeneration = 600;
	maxAddedNeurons = 2;
	xGenerations = 50;
	savePhenotype = false;
	sendGenomeAsSignal = true;
	shouldReopenConnections = true;
	killWhenNotConnected = true;
	colorization = COLOR_NEURALNETWORK;
	environmentType = DEFAULT_ENV;
	maxForce = 1.5;
	maxForceSensor = 806.0; // N*m
	maxTorqueSensor = 100.1;
	consecutiveThresholdViolations = 10;
	numberOfEvaluations = 1;
	// repository="files";
}

Settings::~Settings() {

}
Settings* Settings::instance = 0;
Settings * Settings::getInstance()
{
	if (instance == 0)
	{
		instance = new Settings();
	}
	return instance;
}

void Settings::split_line(string& line, string delim, list<string>& values)
{
	size_t pos = 0;
	while ((pos = line.find(delim, (pos + 0))) != string::npos) {
		string p = line.substr(0, pos);
		values.push_back(p);
		line = line.substr(pos + 1);
	}
	while ((pos = line.find(delim, (pos + 1))) != string::npos) {
		string p = line.substr(0, pos);
		values.push_back(p);
		line = line.substr(pos + 1);
	}

	if (!line.empty()) {
		values.push_back(line);
	}
}

void Settings::openPort() {
	// deprecated
	//packetHandler1 = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION1);
	//packetHandler2 = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION2);
	//char *dev_name = (char*)DEVICENAME;
	//portHandler = dynamixel::PortHandler::getPortHandler(dev_name);

	//if (portHandler->openPort())
	//{
	//	printf("Succeeded to open the port!\n\n");
	//	printf(" - Device Name : %s\n", dev_name);
	//	printf(" - Baudrate    : %d\n\n", portHandler->getBaudRate());
	//}
	//else
	//{
	//	printf("Failed to open the port! [%s]\n", dev_name);
	//	printf("Press any key to terminate...\n");
	//	//		getch();
	//}
}

void Settings::readSettings() {
	bool fileExists = false;
	std::cout << "sceneNum = " << sceneNum << std::endl;
	ifstream file(repository + "/settings" + to_string(sceneNum) + ".csv");
	string morphType;
	int popCounter = 0;

	std::cout << "Looking up settings in: " << repository << "/settings" << to_string(sceneNum) << ".csv" << std::endl;
	if (file.good()) {
		std::cout << "settings found" << std::endl;
		int popCounter = 0;
		string value;
		list<string> values;

		// read the settings file and store the comma seperated values
		while (file.good()) {
			getline(file, value, ','); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			if (value.find('\n') != string::npos) {
				split_line(value, "\n", values);
			}
			else {
				values.push_back(value);
			}
		}
		file.close();

		list<string>::const_iterator it = values.begin();
		for (it = values.begin(); it != values.end(); it++) {
			string tmp = *it;
	//		cout << tmp << endl;
			if (tmp == "#serverMode") {
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				if (tmpInt == 1) {
					cout << "============INSTANCE MODE============" << endl;
					cout << "-------------SERVER MODE-------------" << endl;
					cout << "=====================================" << endl;
					instanceType = INSTANCE_SERVER;
				}
				else {
					instanceType = INSTANCE_REGULAR; 
				}
			}
			if (tmp == "#evolutionType") {
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				switch (tmpInt) {
				case RANDOM_SEARCH:
					evolutionType = RANDOM_SEARCH;
					break;
				case STEADY_STATE:
					evolutionType = STEADY_STATE;
					break;
				case GENERATIONAL:
					evolutionType = GENERATIONAL;
					break;
				case EMBODIED_EVOLUTION:
					evolutionType = EMBODIED_EVOLUTION;
					break;
				}
			}
			else if (tmp == "#fitnessType") {
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				switch (tmpInt) {
				case MOVE:
					fitnessType = MOVE;
					cout << "============FITNESS TYPE=============" << endl;
					cout << "----------MOVE FITNESS TYPE----------" << endl;
					cout << "=====================================" << endl;
					break;
				case SOLAR:
					fitnessType = SOLAR;
					cout << "============FITNESS TYPE=============" << endl;
					cout << "---------SOLAR FITNESS TYPE----------" << endl;
					cout << "=====================================" << endl;

					break;
				case SWIM:
					cout << "============FITNESS TYPE=============" << endl;
					cout << "-------SWIMMING FITNESS TYPE---------" << endl;
					cout << "=====================================" << endl;
					fitnessType = SWIM;
					break;
				case FITNESS_JUMP:
					fitnessType = FITNESS_JUMP;
					cout << "============FITNESS TYPE=============" << endl;
					cout << "----------JUMP FITNESS TYPE----------" << endl;
					cout << "=====================================" << endl;
					break;
				case MOVE_AND_SOLAR:
					fitnessType = MOVE_AND_SOLAR;
					cout << "============FITNESS TYPE=============" << endl;
					cout << "-----MOVE AND SOLAR FITNESS TYPE-----" << endl;
					cout << "=====================================" << endl;
					break;
				}

			}
			else if (tmp == "#environmentType") {
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				switch (tmpInt) {
				case DEFAULT_ENV:
					environmentType = DEFAULT_ENV;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "--INITIALIZING DEFAULT ENVIRONMENT---" << endl;
					cout << "=====================================" << endl;
					break;
				case SUN_BASIC:
					environmentType = SUN_BASIC;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "--INITIALIZING SUN BASIC ENVIRONMENT-" << endl;
					cout << "=====================================" << endl;
					break;
				case SUN_CONSTRAINED:
					environmentType = SUN_CONSTRAINED;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "INITIALIZING SUN CONSTRAINED ENVIRONMENT" << endl;
					cout << "=====================================" << endl;
					break;
				case SUN_BLOCKED:
					environmentType = SUN_BLOCKED;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "------BLOCKED SUN ENVIRONMENT--------" << endl;
					cout << "=====================================" << endl;
					break;
				case SUN_CONSTRAINED_AND_MOVING:
					environmentType = SUN_CONSTRAINED_AND_MOVING;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "INITIALIZING SUN CONSTRAINED AND MOVING ENVIRONMENT" << endl;
					cout << "=====================================" << endl;
					break;
				case WATER_ENV:
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "----INITIALIZING WATER ENVIRONMENT---" << endl;
					cout << "=====================================" << endl;

					environmentType = WATER_ENV;
					break;
				case ROUGH:
					environmentType = ROUGH;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "----INITIALIZING ROUGH ENVIRONMENT---" << endl;
					cout << "=====================================" << endl;

					break;
				case SUN_MOVING:
					environmentType = SUN_MOVING;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "-INITIALIZING SUN MOVING ENVIRONMENT-" << endl;
					cout << "=====================================" << endl;

					break;
				case CONSTRAINED_MOVING_SUN:
					environmentType = CONSTRAINED_MOVING_SUN;
					cout << "===========ENVIRONMENT TYPE==========" << endl;
					cout << "--------CONSTRAINED MOVING SUN-------" << endl;
					cout << "=====================================" << endl;
					break;
				}
			}
			else if (tmp == "#controlType") {
				cout << "========INITIALIZING CONTROL=========" << endl;
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				switch (tmpInt) {
				case ANN_DEFAULT:
					cout << "----------INITIALIZING ANN-----------" << endl;
					controlType = ANN_DEFAULT;
					break;
				case ANN_CUSTOM:
					cout << "-------INITIALIZING CUSTOM ANN-------" << endl;
					controlType = ANN_CUSTOM;
					break;
				case ANN_CPPN:
					cout << "----------INITIALIZING CPPN----------" << endl;
					controlType = ANN_CPPN;
					break;
				case ANN_DISTRIBUTED_UP:
					cout << "----INITIALIZING DISTRIBUTED ANN----" << endl;
					controlType = ANN_DISTRIBUTED_UP;
					break;
				case ANN_DISTRIBUTED_DOWN:
					cout << "----INITIALIZING DISTRIBUTED ANN----" << endl;
					controlType = ANN_DISTRIBUTED_DOWN;
					break;
				case ANN_DISTRIBUTED_BOTH:
					cout << "----INITIALIZING DISTRIBUTED ANN----" << endl;
					controlType = ANN_DISTRIBUTED_BOTH;
					break;
				}
				cout << "=====================================" << endl;
			}
			else if (tmp == "#morphologyType") {
				cout << "=======INITIALIZING MORPHOLOGY=======" << endl;
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				switch (tmpInt) {
				case CAT_MORPHOLOGY:
					cout << "----------INITIALIZING CAT----------" << endl;
					morphologyType = CAT_MORPHOLOGY;
					break;
				case MODULAR_LSYSTEM:
					cout << "----------MODULAR LSYSTEM----------" << endl;
					morphologyType = MODULAR_LSYSTEM;
					break;
				case CUSTOM_MORPHOLOGY:
					cout << "--------CUSTOM MORPHOLOGY----------" << endl;
					morphologyType = CUSTOM_MORPHOLOGY;
					break;
				case MODULAR_CPPN:
					cout << "-----------MODULAR CPPN------------" << endl;
					morphologyType = MODULAR_CPPN;
					break;
				case MODULAR_DIRECT:
					cout << "----------MODULAR DIRECT-----------" << endl;
					morphologyType = MODULAR_DIRECT;
					break;
				case CUSTOM_MODULAR_MORPHOLOGY:
					cout << "-----CUSTOM MODULAR MORPHOLOGY-----" << endl;
					morphologyType = CUSTOM_MODULAR_MORPHOLOGY;
					break;
				case QUADRUPED_GENERATIVE:
					cout << "--QUADRUPED GENERATIVE MORPHOLOGY--" << endl;
					morphologyType = QUADRUPED_GENERATIVE;
					break;
				case QUADRUPED_DIRECT:
					cout << "----QUADRUPED DIRECT MORPHOLOGY----" << endl;
					morphologyType = QUADRUPED_DIRECT;
					break;
				case CUSTOM_SOLAR_GENERATIVE:
					cout << "----SOLAR GENERATIVE MORPHOLOGY----" << endl;
					morphologyType = CUSTOM_SOLAR_GENERATIVE;
					break;
				}
                cout << "=====================================" << endl;
            }

			//if (tmp == "#morphologyType") { // later
			//	it++;
			//	tmp = *it;
			//	int tmpInt = atoi(tmp.c_str());
			//	switch (tmpInt) { 
			//	case NO_MORPHOLOGY: 
			//		morphologyType = NO_MORPHOLOGY; // I don't know why you would want this though
			//		break;
			//	case MODULAR_LSYSTEM:
			//		morphologyType = MODULAR_LSYSTEM;
			//		break;
			//	case MODULAR_CPPN:
			//		morphologyType = MODULAR_CPPN;
			//		break;
			//	case MODULAR_DIRECT:
			//		morphologyType = MODULAR_DIRECT;
			//		break;
			//	case CAT_MORPHOLOGY:
			//		morphologyType = CAT_MORPHOLOGY;
			//		break;
			//	case CUSTOM_MORPHOLOGY:
			//		morphologyType = CUSTOM_MORPHOLOGY;
			//		break;
			//	default:
			//		morphologyType = CAT_MORPHOLOGY;
			//		break;
			//	}
			//}
			else if (tmp == "#selectionType") {
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				switch (tmpInt) {
				case SELECTION_RANDOM:
					selectionType = SELECTION_RANDOM;
					break;
				case SELECTION_PROPORTIONATE:
					selectionType = SELECTION_PROPORTIONATE;
					break;
				}
			}
			else if (tmp == "#replacementType") {
				it++;
				tmp = *it;
				int tmpInt = atoi(tmp.c_str());
				switch (tmpInt) {
				case REPLACEMENT_RANDOM:
					replacementType = REPLACEMENT_RANDOM;
					break;
				case REPLACEMENT_REMOVEWORST:
					replacementType = REPLACEMENT_REMOVEWORST;
					break;
				case REPLACEMENT_PARETOMORPH:
					replacementType = REPLACEMENT_PARETOMORPH;
					break;
				}
			}
			else if (tmp == "#generation") {
				it++;
				tmp = *it;
				generation = atoi(tmp.c_str());
				cout << "generation found : " << generation << endl;
			}
	//		else if (tmp == "#repository") { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//			it++;
	//			tmp = *it;
	//			repository = tmp;
	//		}

			else if (tmp == "#maxGeneration") {
				it++;
				tmp = *it;
				maxGeneration = atoi(tmp.c_str());
			}
			else if (tmp == "#generationInterval") {
				it++;
				tmp = *it;
				xGenerations = atoi(tmp.c_str());
			}

			else if (tmp == "#indCounter") {
				it++;
				tmp = *it;
				individualCounter = atoi(tmp.c_str());
			}

			else if (tmp == "#populationSize") {
				it++;
				tmp = *it;
				populationSize = atoi(tmp.c_str());
				popCounter = populationSize;
				cout << "populationSize found : " << populationSize << endl;
			}
			else if (tmp == "#individuals") {
				it++;
				tmp = *it;
				for (int i = 0; i < popCounter; i++) {
					indNumbers.push_back(atoi(tmp.c_str()));
					it++;
					tmp = *it;
				}
			}
			if (evolutionType == COEVOLUTION) {
				if (tmp == "#coindividuals") {
					it++;
					tmp = *it;
					for (int i = 0; i < popCounter; i++) {
						coIndNumbers.push_back(atoi(tmp.c_str()));
						it++;
						tmp = *it;
					}
				}
				else if (tmp == "#indFits") {
					it++;
					tmp = *it;
					for (int i = 0; i < popCounter; i++) {
						indFits.push_back(atof(tmp.c_str()));
						it++;
						tmp = *it;
					}
				}
			}
			else if (tmp == "#coIndFits") {
				it++;
				tmp = *it;
				for (int i = 0; i < popCounter; i++) {
					coIndFits.push_back(atof(tmp.c_str()));
					it++;
					tmp = *it;
				}
			}
			else if (tmp == "#mutationRate") {
				it++;
				tmp = *it;
				mutationRate = atof(tmp.c_str());
			}
			else if (tmp == "#morphMutRate") {
				it++;
				tmp = *it;
				morphMutRate = atof(tmp.c_str());
			}
			else if (tmp == "#crossover") {
				it++;
				tmp = *it;
				crossover = atoi(tmp.c_str());
			}

			else if (tmp == "#crossoverRate") {
				it++;
				tmp = *it;
				crossoverRate = atof(tmp.c_str());
			}
			else if (tmp == "#agingInds") {
				it++;
				tmp = *it;
				ageInds = atoi(tmp.c_str());
			}
			else if (tmp == "#maxAge") {
				it++;
				tmp = *it;
				maxAge = atoi(tmp.c_str());
			}
			else if (tmp == "#minAge") {
				it++;
				tmp = *it;
				minAge = atoi(tmp.c_str());
			}
			else if (tmp == "#deathProbability") {
				it++;
				tmp = *it;
				deathProb = atof(tmp.c_str());
			}
			else if (tmp == "#lIncrements") {
				it++;
				tmp = *it;
				lIncrements = atoi(tmp.c_str());
			}
			else if (tmp == "#verbose") {
				it++;
				tmp = *it;
				if (atoi(tmp.c_str()) == 0) {
					verbose = false;
				}
				else {
					verbose = true;
				}
			}
			else if (tmp == "#sendGenomeAsSignal") {
				it++;
				tmp = *it;
				if (atoi(tmp.c_str()) == 0) {
					sendGenomeAsSignal = false;
				}
				else {
					sendGenomeAsSignal = true;
				}
			}
			else if (tmp == "#shouldReopenConnections") {
				it++;
				tmp = *it;
				if (atoi(tmp.c_str()) == 0) {
					shouldReopenConnections = false;
				}
				else {
					shouldReopenConnections = true;
				}
			}

			else if (tmp == "#bestIndividual") {
				cout << "found best individual" << endl;
				it++;
				tmp = *it;
				bestIndividual = atoi(tmp.c_str());
			}
			else if (tmp == "#initialSeed") {
				it++;
				tmp = *it;
				seed = atoi(tmp.c_str());
			}
			else if (tmp == "#energyDissipationRate") {
				it++;
				tmp = *it;
				energyDissipationRate = atof(tmp.c_str());
			}

			else if (tmp == "#amountModules") {
				it++;
				tmp = *it;
				amountModules = atoi(tmp.c_str());
			}
			else if (tmp == "#useVarModules") {
				it++;
				tmp = *it;
				useVarModules = atoi(tmp.c_str());
			}
			else if (tmp == "#maxAmountModules") {
				it++;
				tmp = *it;
				maxAmountModules = atoi(tmp.c_str());
			}
			else if (tmp == "#maxForceModules") {
				cout << "found max force modules" << endl;
				it++;
				tmp = *it;
				maxForce = atof(tmp.c_str());
			}
			else if (tmp == "#maxForceSensorModules") {
				cout << "found max force sensor" << endl;
				it++;
				tmp = *it;
				maxForceSensor = atof(tmp.c_str());
			}
			else if (tmp == "#moduleTypes") {
				moduleTypes.clear();
				for (int i = 0; i < amountModules; i++) {
					it++;
					tmp = *it;
					moduleTypes.push_back(atoi(tmp.c_str()));
				}
			}
			else if (tmp == "#maxAmountModulesTypes") {
				maxModuleTypes.clear();
				vector<int> tmpTypes;

				for (int i = 0; i < amountModules; i++) {
					it++;
					tmp = *it;
					vector<int> tmpMaxMods;
					tmpMaxMods.push_back(moduleTypes[i]);
					tmpMaxMods.push_back(atoi(tmp.c_str()));
					maxModuleTypes.push_back(tmpMaxMods);
					tmpMaxMods.clear();
				}
			}
			fileExists = true;
		}
	}
	cout << "Loaded Settings" << endl;
}

void Settings::saveSettings() {
	ofstream settingsFile;
	settingsFile.open(repository + "/settings" + to_string(sceneNum) + ".csv");
	settingsFile << ",#serverMode," << instanceType << "," << endl;
	settingsFile << ",#evolutionType," << evolutionType << "," << endl;
	settingsFile << ",#fitnessType," << fitnessType << "," << endl;
	settingsFile << ",#environmentType," << environmentType << "," << endl;
	settingsFile << ",#morphologyType," << morphologyType << "," << endl;
	settingsFile << ",#selectionType," << selectionType << "," << endl;
	settingsFile << ",#replacementType," << replacementType << "," << endl;
	settingsFile << ",#controlType," << controlType << "," << endl;
	settingsFile << ",#generation," << generation << "," << endl; // set when saving
	settingsFile << ",#maxGeneration," << maxGeneration << "," << endl;
	settingsFile << ",#generationInterval," << xGenerations << "," << endl;
	settingsFile << ",#indCounter," << individualCounter << "," << endl; // set when saving
	settingsFile << ",#populationSize," << populationSize << "," << endl;
	settingsFile << ",#mutationRate," << mutationRate << "," << endl;
	settingsFile << ",#morphMutRate," << morphMutRate << "," << endl;
	settingsFile << ",#crossover," << crossover << "," << endl;
	settingsFile << ",#crossoverRate," << crossoverRate << "," << endl;
	settingsFile << ",#energyDissipationRate," << energyDissipationRate << "," << endl;
	settingsFile << ",#agingInds," << ageInds << "," << endl;
	settingsFile << ",#maxAge," << maxAge << "," << endl;
	settingsFile << ",#minAge," << minAge << "," << endl;
	settingsFile << ",#deathProbability," << deathProb << "," << endl;
	settingsFile << ",#lIncrements," << lIncrements << "," << endl;
	settingsFile << ",#bestIndividual," << bestIndividual << endl; // set when saving
	settingsFile << ",#initialSeed," << seed << "," << endl;
	settingsFile << ",#verbose," << verbose << "," << endl;
	settingsFile << ",#amountModules," << amountModules << "," << endl; // not used
	settingsFile << ",#useVarModules," << useVarModules << "," << endl;
	settingsFile << ",#maxAmountModules," << maxAmountModules << "," << endl;
	settingsFile << ",#sendGenomeAsSignal," << sendGenomeAsSignal << "," << endl;
	settingsFile << ",#shouldReopenConnections," << shouldReopenConnections << "," << endl;

	settingsFile << ",#maxForceModules," << maxForce << "," << endl;
	settingsFile << ",#maxForceSensorModules," << maxForceSensor << "," << endl;
	settingsFile << ",#repository," << repository << "," << endl;

	settingsFile << ",#moduleTypes,";
	for (int i = 0; i < moduleTypes.size(); i++) {
		settingsFile << moduleTypes[i] << ",";
	} settingsFile << endl;

	settingsFile << ",#maxAmountModulesTypes,";
	for (int i = 0; i < maxModuleTypes.size(); i++) {
		settingsFile << maxModuleTypes[i][1] << ",";
	}	settingsFile << endl;

	settingsFile << ",#individuals,";
	for (int i = 0; i < populationSize; i++) {
		settingsFile << indNumbers[i] << ","; // must be set when saving
	} settingsFile << endl;
	if (indFits.size() > 0) {
		settingsFile << ",#indFits,";
		for (int i = 0; i < populationSize; i++) {
			settingsFile << indFits[i] << ","; // must be set when saving
		}
	}	
	settingsFile << endl;

	settingsFile << ",#coindividuals,";
	for (int i = 0; i < coIndNumbers.size(); i++) {
		settingsFile << coIndNumbers[i] << ","; // must be set when saving
	} settingsFile << endl;
	if (coIndFits.size() > 0) {
		settingsFile << ",#coIndFits,";
		for (int i = 0; i < coIndFits.size(); i++) {
			settingsFile << coIndFits[i] << ","; // must be set when saving
		}
	}
	settingsFile << endl;

	settingsFile.close();
}