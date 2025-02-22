#pragma once
#include "MorphologyFactory.h"
#include <iostream>

using namespace std;

MorphologyFactory::MorphologyFactory()
{
}


MorphologyFactory::~MorphologyFactory()
{
}


shared_ptr<Morphology> MorphologyFactory::createMorphologyGenome(int type)
{
	Settings* st = Settings::getInstance();
	RandNum *rn = RandNum::getInstance();
	cout << "Creating morphology of type " << type << endl;
	switch (type){
	case 0:
	{
		
		shared_ptr<Morphology> m_morph(new CAT);
		m_morph->randomNum = RandNum::getInstance();
		m_morph->settings = Settings::getInstance();
		return m_morph;
	}
	case 1: {
//		shared_ptr<Morphology> m_morph(new MultiPurposeLSystemV2);
		shared_ptr<Morphology> m_morph(new ER_LSystem);
		m_morph->randomNum = rn;
		m_morph->settings = st;
		return m_morph;
	}
	case 2: {
		shared_ptr<Morphology> fixedBaseMorph(new FixedBaseMorphology);
		//	fixedBaseMorph->init();
		return fixedBaseMorph;
	}
	case 3: {
		shared_ptr<Morphology> m_morph(new ER_CPPN_Encoding);
		m_morph->randomNum = rn;
		m_morph->settings = st;
		return m_morph;
	}
	case 4: {
		shared_ptr<Morphology> morph(new ER_DirectEncoding);
		morph->randomNum = rn;
		morph->settings = st;
		return morph;
	}
	case 5: {
		shared_ptr<CustomMorphology> morph(new CustomMorphology);
		morph->randomNum = rn;
		morph->settings = st;
		return morph;
	}
	case 7: {
		shared_ptr<Morphology> morph(new ER_LSystem);
		morph->randomNum = rn;
		morph->settings = st;
		return morph;
	}
	case 8: {
		shared_ptr<Morphology> morph(new ER_DirectEncoding);
		morph->randomNum = rn;
		morph->settings = st;
		return morph;
	}
	case 9: {
		shared_ptr<Morphology> morph(new ER_LSystem);
		morph->randomNum = rn;
		morph->settings = st;
		return morph;
	}
	case 11: {
		shared_ptr<Morphology> morph(new ER_DirectEncoding);
		morph->randomNum = rn;
		morph->settings = st;
		return morph;
	}

	default: {
		shared_ptr<Morphology> fixedBaseMorph(new FixedBaseMorphology);
		return fixedBaseMorph;
	}
	}

}

shared_ptr<Morphology> MorphologyFactory::copyMorphologyGenome(shared_ptr<Morphology> parent)
{
	shared_ptr<Morphology> cloneMorphology;
	cloneMorphology = parent->clone();
	//	cout << "return clone" << endl; 
	return cloneMorphology;
}

shared_ptr<Morphology>MorphologyFactory::createBaseMorphologyGenome()
{
	shared_ptr<Morphology> baseMorph(new BaseMorphology);
	return baseMorph; 
}