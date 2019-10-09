#pragma once

/**
 * Implementation for the MAP-Elites algorithm
 */

#include "../EA.h"
#include "../map_elites/Map.hpp"
#include "../map_elites/Evaluator.hpp"
#include <memory>

namespace map_elites {
class MapElites: public EA {
 protected:
  // The actual map to which stores individuals (we use `unique_ptr` to allow
  // for late initialization
  std::unique_ptr<Map> _storage;
  // Evaluator which calculates the behavior of genomes
  std::unique_ptr<Evaluator> _eval;
 public:
  MapElites() {}
  ~MapElites() override {}

  void init() override;
  void selection() override;
  void replacement() override;
  void mutation() override;

  void loadPopulationGenomes();
  void savePopFitness(int) override;
};
}
