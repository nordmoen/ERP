#pragma once
#include "EA.h"
#include "EA_SteadyState.h"
#include "EA_CoEvolution.h"

class EA_Factory 
{
public:
	EA_Factory();
	~EA_Factory();
	shared_ptr<EA> createEA();
};

