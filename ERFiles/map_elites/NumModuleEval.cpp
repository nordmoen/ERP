#include "../map_elites/NumModuleEval.hpp"
#include "../Settings.h"
#include <cassert>

namespace map_elites {
const std::pair<float, float> NumModuleEval::behavior(const std::shared_ptr<Genome> genome) const {
  const auto modules = genome->morph->createdModules;
  float movable = 0.0;
  for(const auto module : modules) {
    // '4' means that the module should be movable
    if(module->type == 4) {
      movable += 1;
    }
  }
  float max = static_cast<float>(Settings::getInstance()->maxAmountModules);
  float total = static_cast<float>(modules.size());
  movable /= max;
  total /= max;
  assert(0.0 <= movable && movable <= 1.0);
  assert(0.0 <= total && total <= 1.0);
  return std::make_pair(total, movable);
}
}
