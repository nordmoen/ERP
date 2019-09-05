#pragma once
#include "ANN.h"
#include "Control.h"
#include "SimpleControl.h"
#include "ANN.h"
#include "CPPN.h"
#include "CustomANN.h"

class ControlFactory
{
public:
	ControlFactory();
	~ControlFactory();
	shared_ptr<Control> createNewControlGenome(int type, Settings* st, RandNum* rn);
	shared_ptr<Control> copyControlGenome(shared_ptr<Control> parentControl);
	RandNum* randomNum;
};

