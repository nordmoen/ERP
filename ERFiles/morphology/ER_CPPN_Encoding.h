#pragma once

#include <vector>
#include "Development.h"
#include <algorithm>
#include "../module/ER_Module.h"
#include "../module/ModuleFactory.h"


using namespace std;


class ER_CPPN_Encoding : public Development
{
public:
	ER_CPPN_Encoding();
	~ER_CPPN_Encoding();

	void init();
	void mutate();

	int initializeGenome(int type);
	
	void createAtPosition(float x, float y, float z);

	int mutateCPPN(float mutationRate);
	int mutateControlERGenome(float mutationRate);
	bool queried = false;
	int maxIterations = 4;
	shared_ptr<Control> cppn;
	void deleteModuleFromGenome(int num);

	void checkControl(int individual, int sceneNum);
	void setPhenValue();
	void create();
	shared_ptr<Morphology> clone() const;
	void update();
	void updateColors();
	float fitness;
	void printSome();

	void checkForceSensors();
	int initializeCPPNEncoding(float initialPosition[3]);

	void initializeGenomeCustom(int type);
	void initializeQuadruped(int type);
	virtual const std::string generateGenome(int individual, float fitness) const override;
	float getFitness();
	bool loadGenome(std::istream &input, int individualNumber);
	void setColors();
	int getMainHandle();
	void savePhenotype(int ind, float fitness);
	int getAmountBrokenModules();
	void symmetryMutation(float mutationRate);
	void crossover(shared_ptr<Morphology>, float crossoverRate);

	vector<shared_ptr<ER_Module>> modules;

protected:
	enum OBJECTTYPE {
		CUBE, 
		BEND, 
		PANEL
	};
	enum CONNECTTYPE {
		FORCE,
		PRISMATIC
	};

	struct MODULEPARAMETERS {
		// State specific parameters
		shared_ptr<MODULEPARAMETERS> clone() const {
			return make_unique<MODULEPARAMETERS>(*this);
		};
		bool expressed = true;
		int maxChilds;
		bool queried = false;

		// not stored in genome
		vector<int> childSiteStates; // which attachment site has which child object. -1 = no child 
		float rgb[3];
		// parameter identifiers
		int handle;
		float color[3] = { 0.45f,0.45f,0.45f };
		shared_ptr<Control> control;
		float moduleColor[3];
		int type = -1; // cube, servo, leaf, etc.

		// for direct encoding
		int parent;
		int parentSite;
		int orientation;
	};

	struct GENOTYPE {
		shared_ptr<GENOTYPE> clone() const {
			return make_unique<GENOTYPE>(*this);
		};
		vector<shared_ptr<MODULEPARAMETERS>> moduleParameters; // one struct of parameters for each state 
		//HORMONEGENOME hormoneGenome;
		
		int amountModules = 1; // initial amount of modules
		int mask1 = 65281;
		int mask2 = 65282;
		int maxIt = 200;
		int dynamic = 16;
		bool useSymmetryMutation = true;
		bool crossover = true;
		float crossoverRate = 0.1f; // at every state, a crossover can occur
								   //void deleteLParameters() { // for when it turns out that lParameters needs to store pointers
								   //	for (int i = 0; i < lParameters.size(); i++) {
								   //		delete lParameters[i];
								   //	
								   //} 
		//LGENOME*::clone() const
		//	LGENOME* clone() const;
	};

public:
	shared_ptr<GENOTYPE> genome;
	

private:
	void checkGenome(int individualNumber, int sceneNum);
};