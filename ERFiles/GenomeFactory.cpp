#include "GenomeFactory.h"
#include "DefaultGenome.h"



GenomeFactory::GenomeFactory()
{
}


GenomeFactory::~GenomeFactory()
{
}

std::shared_ptr<Genome> GenomeFactory::createGenome(const GenomeType& type)
{
	Settings* st = Settings::getInstance();
	switch (type) {
    case GenomeType::Default: {
      if (st->verbose) {
        cout << "Creating default genome" << endl;
      }
      std::unique_ptr<Genome> m_genome(new DefaultGenome);
      m_genome->randomNum = RandNum::getInstance();
      m_genome->settings = Settings::getInstance();
      return m_genome;
    }
  }
  return nullptr;
}

std::shared_ptr<Genome> GenomeFactory::copyGenome(std::shared_ptr<Genome> parent)
{
  std::shared_ptr<Genome> cloneGenome;
	cloneGenome = parent->clone();
	return cloneGenome;
}
