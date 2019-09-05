#pragma once
#include <memory>
#include "Genome.h"
#include "DefaultGenome.h"
//#include "DefaultGenomeVREP.h"

class GenomeFactory
{
public:
	GenomeFactory();
	~GenomeFactory();
	shared_ptr<Genome> createGenome(int type);
	shared_ptr<Genome> copyGenome(shared_ptr<Genome> parentMorphology);
	RandNum* randomNum;
};

