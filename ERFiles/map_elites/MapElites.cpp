#include "../map_elites/MapElites.hpp"

#include "../GenomeFactory.h"
#include "../map_elites/NumModuleEval.hpp"
#include "../morphology/MorphologyFactory.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace map_elites {
  void MapElites::init() {
    const auto st = Settings::getInstance();
    // First initialize underlying storage
    _storage.reset(new Map(std::make_pair(st->maxAmountModules, st->maxAmountModules)));
    _eval.reset(new NumModuleEval);
    // Initialize algorithm with initial population
    GenomeFactory gf;
    for(size_t i = 0; i < settings->initialPopulationSize; ++i){
      const auto genome = gf.createGenome(GenomeType::Default);
      genome->fitness = 0.0;
      genome->individualNumber = i;
      genome->isEvaluated = false;
      nextGenGenomes.push_back(genome);
    }
  }

  void MapElites::mutation() {
    for(auto genome : nextGenGenomes){
      genome->mutate();
    }
  }

  void MapElites::selection() {
    // Ensure that there are no stale genomes to evaluate
    assert(nextGenGenomes.empty());
    nextGenGenomes.clear();
    // Extract potential parents from Map
    const auto parents = _storage->elements();
    // Create factory for morphology copying and genome creation
    MorphologyFactory mfact;
    GenomeFactory gf;
    // Create X new individuals
    for(size_t i = 0; i < settings->populationSize; ++i) {
      // Select parent from Map
      const int parent = randomNum->randInt(parents.size(), 0);
      // Create new empty genome
      const auto genome = gf.createGenome(GenomeType::Default);
      // Copy morphology
      genome->morph = mfact.copyMorphologyGenome(parents[parent]->morph);
      genome->individualNumber = i + settings->indCounter;
      genome->fitness = 0.0;
      genome->isEvaluated = false;
      // Add to be evaluated
      nextGenGenomes.push_back(genome);
    }
    // Apply mutation to all selected genomes
    this->mutation();
    // Save mutated genomes
    for(auto genome : nextGenGenomes) {
      genome->saveGenome(genome->individualNumber);
    }
  }

  void MapElites::replacement() {
    // Try each genome in 'nextGenGenomes' and try to insert into map
    for(const auto genome : nextGenGenomes) {
      const auto behavior = _eval->behavior(genome);
      _storage->insert(behavior, genome);
    }
    // Once everything has been tried we clear the list, preparing for the next
    // batch
    nextGenGenomes.clear();
  }

  void MapElites::loadPopulationGenomes() {
    throw std::runtime_error("Re-loading population not yet supported in MapElites");
  }

  void MapElites::savePopFitness(int generation) {
    std::cout << "MapElites generation: " << generation << std::endl;
    if(_storage != nullptr) {
      const std::string folder = settings->repository + "/map_elites" + std::to_string(settings->sceneNum);
      // Save map to separate CSV file
      std::string map_filename = folder + "/map_generation_" +
          std::to_string(generation) + ".csv";
      ofstream map_csv(map_filename);
      try {
        map_csv << *_storage << std::endl;
      } catch(const std::exception& ex) {
        std::cerr << "Caught exception when trying to write Map to CSV\n\t" <<
            ex.what() << std::endl;
      } catch(...) {
        std::cerr << "Uncaught exception when writing Map!" << std::endl;
      }
      // Re-open statistics file and output data
      try{
        std::string stat_filename = folder + "/map_elites_stats.csv";
        ofstream stats_csv;
        stats_csv.open(stat_filename, std::ios::out | std::ios::app);
        stats_csv << generation << "," << _storage->dimensions().first << "," <<
            _storage->dimensions().second << "," << _storage->size() << "," <<
            _storage->coverage() << "," << _storage->reliability() << "," <<
            _storage->precision() << std::endl;
      } catch(const std::exception& ex) {
        std::cerr << "Caught exception when trying to write statistics to CSV\n\t" <<
            ex.what() << std::endl;
      } catch(...) {
        std::cerr << "Uncaught exception when writing statistics!" << std::endl;
      }
    } else {
      std::cerr << "Could not create output from MapElites for generation " <<
          generation << ", '_storage' is nullptr!" << std::endl;
    }
  }
}
