#pragma once
#include "Environment.h"
#include "MoveEnv.h"
#include "RoughMoveEnv.h"
#include "WaterEnv.h"
#include "TrainingEnvironment.h"
#include "CoEvolutionEnv.h"
#include "EnvPhototaxis.h"
#include <memory>

class EnvironmentFactory
{
public:
	EnvironmentFactory();
	~EnvironmentFactory();
	shared_ptr<Environment> createNewEnvironment(Settings* st, RandNum* rd);
};

