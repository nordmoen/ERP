#pragma once
#include <utility>
#include "../Genome.h"

/**
 * The evaluator should evaluate the behavior of a specified Genome.
 *
 * This class is used by MAP-Elites to insert Genomes into the map. Different
 * evaluators can implement different behavior metrics.
 */

namespace map_elites {
class Evaluator {
 public:
  virtual const std::pair<float, float> behavior(const std::shared_ptr<Genome>) const;
};

class NumModuleEval: public Evaluator {
  const std::pair<float, float> behavior(const std::shared_ptr<Genome>) const override;
};
}
