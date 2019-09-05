#pragma once

#include "EA.h"

class EA_CoEvolution : public EA
{
public:
	EA_CoEvolution();
	~EA_CoEvolution();

	void split_line(string & line, string delim, list<string>& values);

	//vector<shared_ptr<Genome>> nextGenGenomes2; // creating the next generation

	// base functions of EA
	void init();
	void selection();
	void replacement();
	void mutation();
	int co_num = 1000000;
	// unique functions
	void initializePopulation();
	void createNewGenTournament(int tours);
	void selectIndividuals(); // random tournament
	void replaceIndividuals(); // random
	void replaceNewIndividual(int indNum, int sceneNum, float fitness);
	
	void createNewGenRandomSelect();

	//void initNewGenome(int indnum);
	//virtual shared_ptr<Genome> initNewGenome();
	virtual void saveGenome(shared_ptr<Genome>) {};
	void savePopFitness(int generation);
	
	void replaceNewPopRandom(int numAttempts, vector<shared_ptr<Genome>> popGens, vector<shared_ptr<Genome>> newGens);
	bool compareByFitness(const shared_ptr<Genome> a, const shared_ptr<Genome> b);
	void replaceNewRank();
	void loadPopulationGenomes(int scenenum);
};

