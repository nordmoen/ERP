#pragma once
#include <memory>
#include "Genome.h"

enum class GenomeType {
  Default,
};

class GenomeFactory
{
public:
	GenomeFactory();
	~GenomeFactory();
  std::shared_ptr<Genome> createGenome(const GenomeType& type);
  std::shared_ptr<Genome> copyGenome(std::shared_ptr<Genome> parentMorphology);
	RandNum* randomNum;
};

