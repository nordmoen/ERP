#pragma once

/**
 * Evaluator which sums number of modules and number of movable modules
 */

#include "../map_elites/Evaluator.hpp"

namespace map_elites {
class NumModuleEval: public Evaluator {
 public:
  const std::pair<float, float> behavior(const std::shared_ptr<Genome>) const override;
};
}
