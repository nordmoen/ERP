#pragma once
#include "../Genome.h"
#include <memory>
#include <utility>

/**
 * The evaluator should evaluate the behavior of a specified Genome.
 *
 * This class is used by MAP-Elites to insert Genomes into the map. Different
 * evaluators should implement different behavior metrics.
 */

namespace map_elites {
class Evaluator {
 public:
  virtual const std::pair<float, float> behavior(const std::shared_ptr<Genome>) const;
};
}
