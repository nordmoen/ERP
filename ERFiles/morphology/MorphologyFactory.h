#pragma once

#include "BaseMorphology.h"
#include "Morphology.h"
#include "FixedBaseMorphology.h"
#include "ER_LSystem.h"
#include <memory>
#include "CAT.h"
#include "ER_DirectEncoding.h"
#include "CustomMorphology.h"
#include "ER_CPPN_Encoding.h"


class MorphologyFactory
{
public:
	MorphologyFactory();
	~MorphologyFactory();
	virtual shared_ptr<Morphology> createMorphologyGenome(int type);
	virtual shared_ptr<Morphology> copyMorphologyGenome(shared_ptr<Morphology> parentMorphology);
	virtual shared_ptr<Morphology> createBaseMorphologyGenome(); // should always be created
	RandNum* randomNum;
};

