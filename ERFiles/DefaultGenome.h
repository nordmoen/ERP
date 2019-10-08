#pragma once
#include "Genome.h"
#include "RandNum.h"
#include "Settings.h"
#include "control/ControlFactory.h"
#include "morphology/MorphologyFactory.h"
#include <memory>
#include <vector>

class DefaultGenome : public Genome
{
public:
	DefaultGenome();
	
	~DefaultGenome();
	std::shared_ptr<Genome> clone() const override;

	void createInitialMorphology(int individualNumber);

	int age = 0;
	int maxAge = 0;
	int minAge = 0;
	float mutationRate = 0.05f;
	float parentPhenValue;

	void savePhenotype(int indNum, int sceneNum) override;
	void init() override;
	void create() override;
	void update() override;
	void mutate() override;
	bool loadGenome(int indNum, int sceneNum) override;
	bool loadGenome(std::istream &input, int indNum) override;
	void saveGenome(int indNum) override;
	const std::string generateGenome() const override;
	void clearGenome() override;
	void checkGenome() override;
	bool loadMorphologyGenome(int indNum, int sceneNum) override;
	bool loadMorphologyGenome(std::istream &input, int indNum) override;
  std::shared_ptr<Genome> cloneGenome();

	void init_noMorph();
	void createAtPosition(float x, float y, float z) override;

	//void mutate();
	float genomeFitness;  

	void loadBaseMorphology(int indNum, int sceneNum); // old


protected:
	// virtual functions to extend with simulator specific classes
	virtual std::shared_ptr<MorphologyFactory> newMorphologyFactory();
};


