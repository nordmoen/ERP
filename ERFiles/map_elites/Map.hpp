#pragma once

#include "../Genome.h"
#include <memory>
#include <utility>
#include <vector>

namespace map_elites {
/**
 * The 'Map' object represents the storage of individuals in MAP-Elites
 */
class Map {
 protected:
  // Private storage for elements
  std::vector<std::shared_ptr<Genome>> _storage;
  // Dimensions of this map
  const std::pair<size_t, size_t> _dims;
  // Helper method to calculate index offsets into '_storage'
  size_t index(const std::pair<float, float>& index_key) const;

 public:
  // Create a new Map with the given dimensions
  Map(const std::pair<size_t, size_t> dimensions);

  // Get the number of dimensions for this Map
  const std::pair<size_t, size_t>& dimensions() const {return _dims;}

  // Try to insert the Genome.
  //
  // This function will return `true` if the genome was inserted, else `false`.
  // Note that `false` indicates that a better individual already exist for the
  // given behavior.
  bool insert(const std::pair<float, float>& behavior, const shared_ptr<Genome> genome);

  // Access the Genome stored at the given behavior.
  //
  // NOTE: Users must check the returned Genome for `nullptr` as non-assigned
  // behaviors will be returned as `nullptr`!
  const std::shared_ptr<Genome> get(const std::pair<float, float>& behavior) const;

  // Get a list of all individuals stored in the Map
  const std::vector<std::shared_ptr<Genome>> elements() const;

  // Get the number of individuals in the Map
  size_t size() const;
};
}
