#pragma once
#include <vector>
#include <memory>
#include "RandNum.h"
#include "Settings.h"
#include "morphology/Morphology.h"


class Genome
{
public:
	Genome();
	virtual ~Genome();

	Settings* settings;
	RandNum* randomNum;
	shared_ptr<Morphology> morph;
	shared_ptr<Control> control;

	// make vector for multi-objective
	float fitness;
	// vector of fitnesses for multiple evaluations
	vector<float> fitnesses; 

	bool isEvaluated = false; // for client server 
	bool initialized = false;

	int individualNumber;
	virtual void init() = 0;
	virtual void create() = 0;
	virtual void update() = 0;
	virtual shared_ptr<Genome> clone() const = 0;
	virtual void mutate() = 0;
	virtual void createAtPosition(float x, float y, float z) = 0;

	virtual void savePhenotype(int indNum, int sceneNum) = 0;

	virtual bool loadGenome(int indNum, int sceneNum) = 0;
	virtual bool loadGenome(std::istream &input, int indNum) = 0;
	virtual void saveGenome(int indNum) = 0;
	virtual const std::string generateGenome() const = 0; 
	virtual void clearGenome() = 0;
	virtual void checkGenome() = 0; // for debugging
	virtual bool loadMorphologyGenome(int indNum, int sceneNum) = 0;
	virtual bool loadMorphologyGenome(std::istream &input, int indNum) = 0;

};

