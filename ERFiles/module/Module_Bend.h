#pragma once
#include "ER_Module.h"

class Module_Bend :
	public ER_Module
{
public:
	Module_Bend();
	~Module_Bend();
	int init();
	int mutate(float mutationRate);
	int createModule(vector<float> configuration, int relativePosHandle, int parentHandle);
	vector<int> getFreeSites(vector<int>);
	vector<int> getObjectHandles();
	shared_ptr<ER_Module> clone();
	float bendAngle = 0.0;
	void setModuleColor();
	void removeModule(); 
	vector<float> updateModule(vector<float> input);
	stringstream getModuleParams();
	void setModuleParams(vector<string>);
	void createControl() {};
	vector<float> getPosition(); 
	virtual stringstream getControlParams() ;

private:
	int objectPhysics = 8;

};

