#include "EA_VREP.h"

EA_VREP::EA_VREP()
{
}


EA_VREP::~EA_VREP()
{
}

void EA_VREP::init()
{
	gf = unique_ptr<GenomeFactoryVREP>(new GenomeFactoryVREP);
}

void EA_VREP::selection()
{
}

void EA_VREP::replacement()
{
}

void EA_VREP::mutation()
{
}


void EA_VREP::initializePopulation(Settings* st, bool client)
{
	settings = st;
	if (client) {
		for (int i = 0; i < st->populationSize; i++)
		{
			populationGenomes.push_back(gf->createGenome(1));
			populationGenomes[i]->fitness = 0;
			// for easy access of fitness values (used by client-server)
			//popFitness.push_back(0);
		}
	}
	else {
		for (int i = 0; i < st->populationSize; i++)
		{
			populationGenomes.push_back(gf->createGenome(0));
			populationGenomes[i]->fitness = 0;
			// for easy access of fitness values (used by client-server)
			//popFitness.push_back(0);
		}
	}
}
