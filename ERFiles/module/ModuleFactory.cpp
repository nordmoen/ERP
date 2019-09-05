#pragma once
#include "ModuleFactory.h"
#include <iostream>


using namespace std; 

ModuleFactory::ModuleFactory()
{
}

ModuleFactory::~ModuleFactory()
{
}

shared_ptr<ER_Module> ModuleFactory::createModuleGenome(int moduleType, Settings* st, RandNum* rn) {
	switch (moduleType) {
	case DEFAULTMODULE:
	{
		cout << "ERROR: Module not specified yet, see ModuleFactory.cpp" << endl; 
		return NULL;
	}
	case CUBE: 
	{
	//	cout << "creating cube genome" << endl;
		shared_ptr<ER_Module> module(new Module_Cube);
		module->randomNum = rn;
		module->settings = st;
		module->type = CUBE;
		module->createControl(); 
		return module;
	}
	//case BEND:
	//{
	////	cout << "creating bend genome" << endl;
	//	shared_ptr<ER_Module> module(new Module_Bend);
	//	module->randomNum = rn;
	//	module->settings = st;
	//	module->type = BEND;
	//	module->createControl();
	//	return module;
	//}
	case LEAF:
	{
	//	cout << "creating leaf genome" << endl;
		shared_ptr<ER_Module> module(new Module_Leaf);
		module->randomNum = rn;
		module->settings = st;
		module->type = LEAF;
		module->createControl();
		return module;
	}
	case SERVO:
	{
		if (st->evolutionType == st->EMBODIED_EVOLUTION) {
			// used to be to evolve real robot directly
		}
		else {
			shared_ptr<ER_Module> module(new Module_Servo);
			module->randomNum = rn;
			module->settings = st;
			module->type = SERVO;
			module->createControl();
			return module;
		}
	}
	/*case RECTANGLE:
	{
		shared_ptr<ER_Module> module(new Module_Rectangle);
		module->randomNum = rn;
		module->settings = st;
		module->type = RECTANGLE;
		module->createControl();
		return module;
	}*/
	case LEAFCHLOE:
	{
	//	cout << "creating leaf chloe genome" << endl; 
		shared_ptr<ER_Module> module(new Module_LeafChloe);
		module->randomNum = rn;
		module->settings = st;
		module->type = LEAFCHLOE;
		module->createControl();
		return module;
	}
	//case BRAIN:
	//{
	////	cout << "creating brain genome" << endl;
	//	shared_ptr<ER_Module> module(new Module_Brain);
	//	module->randomNum = rn;
	//	module->settings = st;
	//	module->type = BRAIN;
	//	module->createControl();
	//	return module;
	//}
	case 8:
	{
	//	cout << "creating PLantA genome" << endl;
		shared_ptr<ER_Module> module(new Module_APlantBase);
		module->randomNum = rn;
		module->settings = st;
		module->type = 8;
		module->createControl();
		return module;
	}	
	//case 9:
	//{
	////	cout << "creating spring genome" << endl;
	//	shared_ptr<ER_Module> module(new Module_Spring);
	//	module->randomNum = rn;
	//	module->settings = st;
	//	module->type = 9;
	//	module->createControl();
	//	return module;
	//}
	case 11:
	{
		shared_ptr<ER_Module> module(new Module_Solar);
		module->randomNum = rn;
		module->settings = st;
		module->type = 11;
		module->createControl();
		return module;
	}
	/*case 12:
	{
		shared_ptr<ER_Module> module(new Module_Head);
		module->randomNum = rn;
		module->settings = st;
		module->type = 12;
		module->createControl();
		return module;
	}
*/
	case 13:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 13;
		module->createControl();
		module->filename = "C_Brain.ttm";
		return module;
	}
	case 14:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 14;
		module->createControl();
		module->filename = "C_Wheel.ttm";
		return module;
	}
	case 15:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 15;
		module->createControl();
		module->filename = "C_Sensor.ttm";
		return module;
	}
	case 16:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 16;
		module->createControl();
		module->filename = "C_Servo.ttm";
		return module;
	}
	case 17:
	{
		shared_ptr<ER_Module> module(new Module_Bone);
		module->randomNum = rn;
		module->settings = st;
		module->type = 17;
		module->createControl();
		module->filename = "C_Bone";
		return module;
	}

	case 30:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 30;
		module->createControl();
		module->filename = "Ant_Leg.ttm";
		return module;
	}
	case 31:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 31;
		module->createControl();
		module->filename = "Snake_Module.ttm";
		return module;
	}
	case 32:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 32;
		module->createControl();
		module->filename = "NAO_Head.ttm";
		return module;
	}
	case 33:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 33;
		module->createControl();
		module->filename = "NAO_Arm.ttm";
		return module;
	}
	case 34:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 34;
		module->createControl();
		module->filename = "UR3_Module.ttm";
		return module;
	}
	case 35:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 35;
		module->createControl();
		module->filename = "Hex_Module.ttm";
		return module;
	}
	case 44:
	{
		shared_ptr<ER_Module> module(new Module_Misc);
		module->randomNum = rn;
		module->settings = st;
		module->type = 44;
		module->createControl();
		module->filename = "Excavator_Module.ttm";
		return module;
	}
	default:
	{
		cout << "ERROR: Module type not specified, returning NULL" << endl; 
		return NULL;
	}

	}
	return NULL;
}

shared_ptr<ER_Module> ModuleFactory::copyModuleGenome(shared_ptr<ER_Module> parent)
{
	unique_ptr<ControlFactory> controlFactory(new ControlFactory);
//	ControlFactory *controlFactory = new ControlFactory(); 
	shared_ptr<ER_Module> cloneModule;
	cloneModule = parent->clone();
	if (cloneModule->control != NULL) {
		cloneModule->control = controlFactory->copyControlGenome(parent->control);
	}
	return cloneModule;
}

