#include "../map_elites/NumModuleEval.hpp"
#include "../Settings.h"
#include <cassert>

namespace map_elites {
const std::pair<float, float> NumModuleEval::behavior(const std::shared_ptr<Genome> genome) const {
  const auto modules = genome->morph->createdModules;
  float movable, non_movable;
  for(const auto module : modules) {
    if(module->type == 4) {
      movable += 1;
    } else {
      non_movable += 1;
    }
  }
  float max = static_cast<float>(Settings::getInstance()->maxAmountModules);
  movable /= max;
  non_movable /= max;
  assert(0.0 <= movable && movable <= 1.0);
  assert(0.0 <= non_movable && non_movable <= 1.0);
  return std::make_pair(non_movable, movable);
}
}
