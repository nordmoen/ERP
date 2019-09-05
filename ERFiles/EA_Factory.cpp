#include "EA_Factory.h"


EA_Factory::EA_Factory()
{
}


EA_Factory::~EA_Factory()
{
}


shared_ptr<EA> EA_Factory::createEA()
{
	Settings* st = Settings::getInstance();
	int type = st->evolutionType;
	switch (type) {
	case 1:
	{
		if (st->verbose) {
			cout << "Steady state EA" << endl;
		}
		unique_ptr<EA> m_ea(new EA_SteadyState);
		m_ea->randomNum = RandNum::getInstance();
		m_ea->settings = Settings::getInstance();
		return m_ea;
	}
	case 6: { // TODO: Somehow this does not work if I say 'st->COEVOLUTION', anyone know why?
		if (st->verbose) {
			cout << "Co-evolution EA" << endl;
		}
		unique_ptr<EA> m_ea(new EA_CoEvolution);
		m_ea->randomNum = RandNum::getInstance();
		m_ea->settings = st;
		return m_ea;
	}
	default:
		if (st->verbose) {
			cout << "Steady state EA" << endl;
		}
		unique_ptr<EA> m_ea(new EA_SteadyState);
		m_ea->randomNum = RandNum::getInstance();
		m_ea->settings = st;
		return m_ea;
	}
	return unique_ptr<EA>();
}