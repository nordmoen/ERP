#include "EA_CoEvolution.h"
#include <algorithm>


EA_CoEvolution::EA_CoEvolution()
{
}


EA_CoEvolution::~EA_CoEvolution()
{
}

void EA_CoEvolution::split_line(string& line, string delim, list<string>& values)
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

void EA_CoEvolution::init()
{
	initializePopulation();
}

void EA_CoEvolution::selection()
{
	// createNewGenRandomSelect();
	createNewGenTournament(2);
}

void EA_CoEvolution::replacement()
{
	populationGenomes = nextGenGenomes;
	populationGenomes2 = nextGenGenomes2;
	/*
	if (populationGenomes.size() > 0) {
		// number of attempts means how many times the new individuals should be checked against the existing population
		replaceNewPopRandom(2,populationGenomes,nextGenGenomes); // int is amount trials comparing offspring to existing population
		replaceNewPopRandom(2,populationGenomes2,nextGenGenomes2); // int is amount trials comparing offspring to existing population
		//replaceNewRank(); 
	}
	else {
		populationGenomes = nextGenGenomes;
	}
	if (populationGenomes2.size() > 0) {
		// number of attempts means how many times the new individuals should be checked against the existing population
		replaceNewPopRandom(2, populationGenomes, nextGenGenomes); // int is amount trials comparing offspring to existing population
		replaceNewPopRandom(2, populationGenomes2, nextGenGenomes2); // int is amount trials comparing offspring to existing population
		//replaceNewRank(); 
	}
	else {
		populationGenomes2 = nextGenGenomes2;
	}
	*/
}

void EA_CoEvolution::mutation() {
	for (int i = 0; i < nextGenGenomes.size(); i++) {
		nextGenGenomes[i]->mutate();
	}
	for (int i = 0; i < nextGenGenomes2.size(); i++) {
		nextGenGenomes2[i]->mutate();
	}
}

void EA_CoEvolution::initializePopulation()
{
	unique_ptr<GenomeFactory> gf = unique_ptr<GenomeFactory>(new GenomeFactory);
	for (int i = 0; i < settings->populationSize; i++)
	{
		nextGenGenomes.push_back(gf->createGenome(1));
		nextGenGenomes[i]->fitness = 0;
		nextGenGenomes[i]->individualNumber = i;
		nextGenGenomes2.push_back(gf->createGenome(1));
		nextGenGenomes2[i]->fitness = 0;
		nextGenGenomes2[i]->individualNumber = i;
	}
	gf.reset();
}

void EA_CoEvolution::createNewGenTournament(int tours) {
	nextGenGenomes.clear();
	nextGenGenomes2.clear();
	//	nextGenFitness.clear();
	shared_ptr<MorphologyFactory> mfact(new MorphologyFactory);
	for (int i = 0; i < populationGenomes.size(); i++) {
		vector<int> parents;
		for (int j = 0; j < tours; j++) {
			parents.push_back(randomNum->randInt(populationGenomes.size(), 0));
		}
		int bestParent = 0;
		float bestParentFit = -10000;
		for (int j = 0; j < parents.size(); j++) {
			if (populationGenomes[parents[j]]->fitness > bestParentFit) {
				bestParentFit = populationGenomes[parents[j]]->fitness;
				bestParent = parents[j];
			}
		}
		nextGenGenomes.push_back(unique_ptr<DefaultGenome>(new DefaultGenome()));
		nextGenGenomes[i]->morph = mfact->copyMorphologyGenome(populationGenomes[bestParent]->morph->clone()); // deep copy
		nextGenGenomes[i]->individualNumber = i + settings->indCounter;
		nextGenGenomes[i]->fitness = 0; // Ensure the fitness is set to zero. 
		nextGenGenomes[i]->isEvaluated = false; // This should also be set, just to be sure. 
	}

	for (int i = 0; i < populationGenomes2.size(); i++) {
		vector<int> parents;
		for (int j = 0; j < tours; j++) {
			parents.push_back(randomNum->randInt(populationGenomes2.size(), 0));
		}
		int bestParent = 0;
		float bestParentFit = -10000;
		for (int j = 0; j < parents.size(); j++) {
			if (populationGenomes2[parents[j]]->fitness > bestParentFit) {
				bestParentFit = populationGenomes2[parents[j]]->fitness;
				bestParent = parents[j];
			}
		}
		nextGenGenomes2.push_back(unique_ptr<DefaultGenome>(new DefaultGenome()));
		nextGenGenomes2[i]->morph = mfact->copyMorphologyGenome(populationGenomes2[bestParent]->morph->clone()); // deep copy
		nextGenGenomes2[i]->individualNumber = i + settings->indCounter + 1000000;
		nextGenGenomes2[i]->fitness = 0; // Ensure the fitness is set to zero. 
		nextGenGenomes2[i]->isEvaluated = false; // This should also be set, just to be sure. 
	}

	mutation();
	// saving genomes
	for (int i = 0; i < nextGenGenomes.size(); i++) {
		nextGenGenomes[i]->saveGenome(nextGenGenomes[i]->individualNumber);
	}

	for (int i = 0; i < nextGenGenomes2.size(); i++) {
		nextGenGenomes2[i]->saveGenome(nextGenGenomes2[i]->individualNumber);
	}

	mfact.reset();
}


void EA_CoEvolution::createNewGenRandomSelect() {
	nextGenGenomes.clear();
	nextGenGenomes2.clear();
	//	nextGenFitness.clear();
	shared_ptr<MorphologyFactory> mfact(new MorphologyFactory);
	for (int i = 0; i < populationGenomes.size(); i++) {
		int parent = randomNum->randInt(populationGenomes.size(), 0);
		if (settings->verbose) {
			std::cout << "Selecting parent " << parent << " with fitness " << populationGenomes[i]->fitness << " individual number is " << populationGenomes[i]->individualNumber << std::endl;
			std::cout << "^ will get ind number " << i + settings->indCounter << std::endl;
		}
		//nextGenFitness.push_back(-100.0);
		nextGenGenomes.push_back(unique_ptr<DefaultGenome>(new DefaultGenome()));
		if (settings->verbose) {
			std::cout << "About to deep copy genome" << endl;
		}
		nextGenGenomes[i]->morph = mfact->copyMorphologyGenome(populationGenomes[parent]->morph->clone()); // deep copy
		if (settings->verbose) {
			std::cout << "Done with deep copy genome" << endl;
		}
		nextGenGenomes[i]->individualNumber = i + settings->indCounter;
		nextGenGenomes[i]->fitness = 0; // Ensure the fitness is set to zero. 
		nextGenGenomes[i]->isEvaluated = false; // This should also be set, just to be sure. 
	}
	for (int i = 0; i < populationGenomes2.size(); i++) {
		int parent = randomNum->randInt(populationGenomes2.size(), 0);
		if (settings->verbose) {
			std::cout << "Selecting parent " << parent << " with fitness " << populationGenomes2[i]->fitness << " individual number is " << populationGenomes[i]->individualNumber << std::endl;
			std::cout << "^ will get ind number " << i + settings->indCounter << std::endl;
		}
		//nextGenFitness.push_back(-100.0);
		nextGenGenomes2.push_back(unique_ptr<DefaultGenome>(new DefaultGenome()));
		if (settings->verbose) {
			std::cout << "About to deep copy genome" << endl;
		}
		nextGenGenomes2[i]->morph = mfact->copyMorphologyGenome(populationGenomes2[parent]->morph->clone()); // deep copy
		if (settings->verbose) {
			std::cout << "Done with deep copy genome" << endl;
		}
		nextGenGenomes2[i]->individualNumber = i + settings->indCounter;
		nextGenGenomes2[i]->fitness = 0; // Ensure the fitness is set to zero. 
		nextGenGenomes2[i]->isEvaluated = false; // This should also be set, just to be sure. 
	}
	if (settings->verbose) {
		std::cout << "Mutating next gen genomes of size: " << nextGenGenomes.size() << std::endl;
	}
	mutation();
	// saving genomes
	for (int i = 0; i < nextGenGenomes.size(); i++) {
		nextGenGenomes[i]->saveGenome(nextGenGenomes[i]->individualNumber);
		// Used to debug
		// populationGenomes[i]->saveGenome(-populationGenomes[i]->individualNumber);
	}

	for (int i = 0; i < nextGenGenomes.size(); i++) {
		nextGenGenomes[i]->saveGenome(nextGenGenomes[i]->individualNumber + co_num);
	}

	mfact.reset();
}





void EA_CoEvolution::savePopFitness(int generation) {
	cout << "SAVING GENERATION COEVOLUTION" << endl << endl;
	settings->indFits.clear();
	settings->indNumbers.clear();
	settings->coIndFits.clear();
	settings->coIndNumbers.clear();
	ofstream savePopFile;
	string saveFileName;
	saveFileName = settings->repository + "/SavedGenerations" + to_string(settings->sceneNum) + ".csv";
	savePopFile.open(saveFileName.c_str(), ios::out | ios::ate | ios::app);
	savePopFile << "generation " << generation << ": ,";
	for (int i = 0; i < populationGenomes.size(); i++) {
		savePopFile /*<< " ind " << i << ": " */ << populationGenomes[i]->fitness << ",";
		settings->indFits.push_back(populationGenomes[i]->fitness);
		settings->indNumbers.push_back(populationGenomes[i]->individualNumber);
	}
	float avgFitness = 0;
	for (int i = 0; i < populationGenomes.size(); i++) {
		avgFitness += populationGenomes[i]->fitness;
	}
	avgFitness = avgFitness / populationGenomes.size();
	savePopFile << "avg: ," << avgFitness << ",";
	int bestInd = 0;
	float bestFitness = 0;
	for (int i = 0; i < populationGenomes.size(); i++) {
		if (bestFitness < populationGenomes[i]->fitness) {
			bestFitness = populationGenomes[i]->fitness;
			bestInd = i;
		}
	}
	savePopFile << "ind: ," << populationGenomes[bestInd]->individualNumber << ",";
	savePopFile << "fitness: ," << bestFitness << ",";
	savePopFile << "individuals: ,";
	for (int i = 0; i < populationGenomes.size(); i++) {
		savePopFile << populationGenomes[i]->individualNumber << ",";
	}
	savePopFile << "generation " << generation << ": ,";



	// pop 2
	for (int i = 0; i < populationGenomes2.size(); i++) {
		savePopFile /*<< " ind " << i << ": " */ << populationGenomes2[i]->fitness << ",";
		settings->coIndFits.push_back(populationGenomes2[i]->fitness);
		settings->coIndNumbers.push_back(populationGenomes2[i]->individualNumber);

	}
	float avgFitness2 = 0;
	for (int i = 0; i < populationGenomes2.size(); i++) {
		avgFitness2 += populationGenomes2[i]->fitness;
	}
	avgFitness2 = avgFitness2 / populationGenomes2.size();
	savePopFile << "avg: ," << avgFitness << ",";
	int bestInd2 = 0;
	float bestFitness2 = 0;
	for (int i = 0; i < populationGenomes2.size(); i++) {
		if (bestFitness2 < populationGenomes2[i]->fitness) {
			bestFitness2 = populationGenomes2[i]->fitness;
			bestInd2 = i;
		}
	}
	savePopFile << "ind: ," << populationGenomes2[bestInd2]->individualNumber << ",";
	savePopFile << "fitness: ," << bestFitness2 << ",";
	savePopFile << "individuals: ,";
	for (int i = 0; i < populationGenomes2.size(); i++) {
		savePopFile << populationGenomes2[i]->individualNumber << ",";
	}
	savePopFile << endl;


	savePopFile.close();
	cout << "GENERATION SAVED" << endl;
}

void EA_CoEvolution::replaceNewPopRandom(int numAttempts, vector<shared_ptr<Genome>> popGens, vector<shared_ptr<Genome>> nextGens)
{
	cout << "REPLACINGPOP::::::::::::::" << endl;
	for (int p = 0; p < popGens.size(); p++) {
		for (int n = 0; n < numAttempts; n++) {
			int currentInd = randomNum->randInt(popGens.size(), 0);
			if (nextGens[p]->fitness >= popGens[currentInd]->fitness) {
				cout << "replacement: " << nextGens[p]->individualNumber << " replaces " << popGens[currentInd]->individualNumber << endl;
				cout << "replacement: " << nextGens[p]->fitness << " replaces " << popGens[currentInd]->fitness << endl;
				popGens[currentInd].reset();
				popGens[currentInd] = nextGens[p]->clone(); // new DefaultGenome();
				break;
			}
			else if (n == (numAttempts - 1)) {
				// delete genome file
				stringstream ss;
				ss << settings->repository + "/genomes" << settings->sceneNum << "/genome" << nextGens[p]->individualNumber << ".csv";
				string genomeFileName = ss.str();
				stringstream ssp;
				ssp << settings->repository + "/genomes" << settings->sceneNum << "/phenotype" << nextGens[p]->individualNumber << ".csv";
				string phenotypeFileName = ssp.str();
				//	genomeFileName << indNum << ".csv";
				cout << "Removing " << nextGens[p]->individualNumber << endl;
				remove(genomeFileName.c_str());
				remove(phenotypeFileName.c_str());
			}
		}
	}
	cout << "REPLACED POP" << endl;
}

bool EA_CoEvolution::compareByFitness(const shared_ptr<Genome> a, const shared_ptr<Genome> b)
{
	return a->fitness > b->fitness;
}

void EA_CoEvolution::replaceNewRank()
{
	vector<shared_ptr<Genome>> populationGenomesBuffer;
	// create one big population. Just store the pointers in the buffer. 
	for (int i = 0; i < populationGenomes.size(); i++) {
		populationGenomesBuffer.push_back(populationGenomes[i]);
	}
	for (int i = 0; i < nextGenGenomes.size(); i++) {
		populationGenomesBuffer.push_back(nextGenGenomes[i]);
	}

	// There were some individuals that got an odd fitness value, this should not happen anymore, but just in case, added a cerr.
	for (int i = 0; i < populationGenomes.size(); i++) {
		if (populationGenomesBuffer[i]->fitness > 100) {
			std::cerr << "ERROR: Note that the fitness wasn't set correctly. Giving individual " << populationGenomes[i]->individualNumber << " a fitness of 0" << std::endl;
			populationGenomesBuffer[i]->fitness = 0;
		}
	}

	// sort population on fitness
	// TODO
//	std::sort(populationGenomesBuffer.begin(), populationGenomesBuffer.end(), compareByFitness);

	// remove all individuals on the bottom of the list. 
	while (populationGenomesBuffer.size() > populationGenomes.size()) {
		populationGenomesBuffer.pop_back(); 
	}

	// The buffer can now replace the existing populationGenomes
	populationGenomes = populationGenomesBuffer;  
	// ^ This swap should kill all objects no referenced to anymore. Without smart pointers this looks dangerous as hell. 

	// Now delete all nextGenGenomes that didn't make it in the populationGenomes
	for (int i = 0; i < nextGenGenomes.size(); i++) {
		bool deleteGenome = true;
		for (int j = 0; j < populationGenomes.size(); j++) { // I guess I could just compare pointers instead.
			if (nextGenGenomes[i]->individualNumber == populationGenomes[j]->individualNumber) {
				// this particular next genome is in the population so it doesn't need to be deleted. 
				deleteGenome = false;
				break;
			}
		}
		// if the if statement in the previous look was never true, the genome will now be deleted. 
		if (deleteGenome == true) {
			// delete genome file
			stringstream ss;
			ss << settings->repository + "/genomes" << settings->sceneNum << "/genome" << nextGenGenomes[i]->individualNumber << ".csv";
			string genomeFileName = ss.str();
			stringstream ssp;
			ssp << settings->repository + "/genomes" << settings->sceneNum << "/phenotype" << nextGenGenomes[i]->individualNumber << ".csv";
			string phenotypeFileName = ssp.str();
			// genomeFileName << indNum << ".csv";
			// cout << "Removing " << nextGenGenomes[i]->individualNumber << endl;
			remove(genomeFileName.c_str());
			remove(phenotypeFileName.c_str());
		}
	}
	populationGenomesBuffer.clear();
	cout << "REPLACED POP RANKED" << endl;
}


void EA_CoEvolution::loadPopulationGenomes(int sceneNum)
{
	unique_ptr<GenomeFactory> gf = unique_ptr<GenomeFactory>(new GenomeFactory);
	for (int i = 0; i < settings->indNumbers.size(); i++) {
		cout << "loading individual " << settings->indNumbers[i] << endl;
		populationGenomes.push_back(gf->createGenome(1));
		populationGenomes[i]->loadMorphologyGenome(settings->indNumbers[i], settings->sceneNum);
		//cout << "Make sure the following is correct" << endl;
		populationGenomes[i]->fitness = settings->indFits[i];
		populationGenomes[i]->individualNumber = settings->indNumbers[i];
		//cout << "called fitness = " << popFitness[i] << endl;
	}
	for (int i = 0; i < settings->coIndNumbers.size(); i++) {
		cout << "loading individual " << settings->coIndNumbers[i] << endl;
		populationGenomes2.push_back(gf->createGenome(1));
		populationGenomes2[i]->loadMorphologyGenome(settings->coIndNumbers[i], settings->sceneNum);
		//cout << "Make sure the following is correct" << endl;
		populationGenomes2[i]->fitness = settings->coIndFits[i];
		populationGenomes2[i]->individualNumber = settings->coIndNumbers[i];
		//cout << "called fitness = " << popFitness[i] << endl;
	}

	gf.reset();
}