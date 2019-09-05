#pragma once
#include "EA.h"
#include "GenomeFactory.h"

class EA_VREP :
	public EA
{
public:
	EA_VREP();
	~EA_VREP();
	unique_ptr <GenomeFactory> gf;
	void init();
	void selection();
	void replacement();
	void mutation();

	void initNewGenome(Settings* st, bool client);
	void loadIndividual(int individualNum, int sceneNum);
	void initializePopulation(Settings* st, bool client);
	void loadBestIndividualGenome(int sceneNum);
};

