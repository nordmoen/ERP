#include "GenomeFactory.h"



GenomeFactory::GenomeFactory()
{
}


GenomeFactory::~GenomeFactory()
{
}

shared_ptr<Genome> GenomeFactory::createGenome(int type)
{
	Settings* st = Settings::getInstance();
	switch (type) {
	case 1:
	{
		if (st->verbose) {
			cout << "Creating default genome" << endl;
		}
		unique_ptr<Genome> m_genome(new DefaultGenome);
		m_genome->randomNum = RandNum::getInstance();
		m_genome->settings = Settings::getInstance();
		//cout << m_genome->settings->COLOR_LSYSTEM << endl;
		return m_genome;
	}
	case 0: {
		if (st->verbose) {
			cout << "Creating default genome" << endl;
		}
		unique_ptr<Genome> m_genome(new DefaultGenome);
		m_genome->randomNum = RandNum::getInstance();
		m_genome->settings = Settings::getInstance();
		//cout << m_genome->settings->COLOR_LSYSTEM << endl;
		return m_genome;
		//	if (st->verbose) {
	//		cout << "Creating default V-REP genome" << endl;
	//	}
	//	unique_ptr<Genome> m_genome(new DefaultGenomeVREP);
	//	m_genome->randomNum = rn;
	//	m_genome->settings = st;
	//	return m_genome;
	}
	}
	return unique_ptr<Genome>();
}

shared_ptr<Genome> GenomeFactory::copyGenome(shared_ptr<Genome> parent)
{
	shared_ptr<Genome> cloneGenome;
	cloneGenome = parent->clone();
	return cloneGenome;
}
