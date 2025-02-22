#include "EnvironmentFactory.h"
#include <iostream>
#include <memory>
using namespace std;

EnvironmentFactory::EnvironmentFactory()
{
}


EnvironmentFactory::~EnvironmentFactory()
{
}

shared_ptr<Environment> EnvironmentFactory::createNewEnvironment(Settings* st, RandNum* rd) {

	//cout << "loading " << st->environmentType << " should be " << st->ENV_SWITCHOBJECTIVE <<  endl;
//	cout << ">>>///???..." << endl;
	if (st->environmentType == st->DEFAULT_ENV) {
		shared_ptr<Environment> moveEnv(new MoveEnv);
		moveEnv->settings = st;
		moveEnv->randNum = rd;
		return moveEnv;
	}
	//else if (st->environmentType == st->SUN_BASIC) {
	//	shared_ptr<Environment> basicEnv(new BasicSunEnv);
	//	basicEnv->settings = st;
	//	return basicEnv;
	//}
	//else if (st->environmentType == st->SUN_CONSTRAINED) {
	//	shared_ptr<Environment> cEnv(new ConstrainedSunEnv);
	//	cEnv->settings = st;
	//	return cEnv;
	//}
	//else if (st->environmentType == st->SUN_MOVING) {
	//	shared_ptr<Environment> env(new MovingSunEnv);
	//	env->settings = st;
	//	return env;
	//}
	//else if (st->environmentType == st->SUN_CONSTRAINED_AND_MOVING) {
	//	shared_ptr<Environment> moveAndSun(new MoveAndSun);
	//	moveAndSun->settings = st;
	//	moveAndSun->type = 0;
	//	return moveAndSun;
	//}
	//else if (st->environmentType == st->ENV_SWITCHOBJECTIVE) {
	//	shared_ptr<Environment> moveAndSun(new MoveAndSun);
	//	moveAndSun->settings = st;
	//	moveAndSun->type = 1;
	//	return moveAndSun;
	//}
	else if (st->environmentType == st->ROUGH) {
		shared_ptr<Environment> roughMoveEnv(new RoughMoveEnv);
		roughMoveEnv->settings = st;
		roughMoveEnv->randNum = rd;
		return roughMoveEnv;
	}
	else if (st->environmentType == st->WATER_ENV) {
		shared_ptr<Environment> waterEnv(new WaterEnv);
		waterEnv->settings = st;
		waterEnv->randNum = rd;
		return waterEnv;
	}
	else if (st->environmentType == st->TRAINING_ENVIRONMENT) {
		shared_ptr<Environment> env(new TrainingEnvironment);
		env->settings = st;
		env->randNum = rd;
		return env;
	}
	else if (st->environmentType == st->CO_ENVIRONMENT) {
		shared_ptr<Environment> env(new CoEvolutionEnv);
		env->settings = st;
		env->randNum = rd;
		return env;
	}
	else if (st->environmentType == st->ENV_PHOTOTAXIS) {
		shared_ptr<Environment> moveEnv(new EnvPhototaxis);
		moveEnv->settings = st;
		moveEnv->randNum = rd;
		return moveEnv;
	}
	else { // default
		shared_ptr<Environment> moveEnv(new MoveEnv);
		moveEnv->settings = st;
		moveEnv->randNum = rd;
		return moveEnv;
	}
	//else if (st->environmentType == st->SUN_BLOCKED) {
	//	shared_ptr<Environment> env(new BlockingSunEnv);
	//	env->settings = st;
	//	return env;
	//}
	//else if (st->environmentType == st->CONSTRAINED_MOVING_SUN) {
	//	cout << "CONSTRAINED AND MOVING" << endl;
	//	shared_ptr<Environment> env(new ConstrainedSunEnv);
	//	env->settings = st;
	//	env->type = 1;
	//	return env;
	//}
	//else if (st->environmentType == st->ENV_FOURSUNS) {
	//	cout << "CONSTRAINED AND MOVING" << endl;
	//	shared_ptr<Environment> env(new MovingSunEnv);
	//	env->settings = st;
	//	env->type = 1;
	//	return env;
	//}

}

