#include "../map_elites/Map.hpp"
#include <cassert>
#include <cmath>

namespace map_elites {
  Map::Map(const std::pair<size_t, size_t> dimensions): _dims(dimensions) {
    _storage.resize(_dims.first * _dims.second);
    assert(_storage.size() == _dims.first * _dims.second);
  }

  size_t Map::index(const std::pair<float, float>& index_key) const {
    // Ensure that keys are in range [0, 1]
    assert(0.0 <= index_key.first && index_key.first <= 1.0);
    assert(0.0 <= index_key.second && index_key.second <= 1.0);
    const size_t x = static_cast<size_t>(std::round(index_key.first * (_dims.first - 1)));
    const size_t y = static_cast<size_t>(std::round(index_key.second * (_dims.second - 1)));
    //std::cout << "Calculating index for: [" << index_key.first << ", " <<
        //index_key.second << "], index: " << (y * _dims.first + x) << " [" << x
        //<< ", " << y << "], Dims: [" << _dims.first << ", " << _dims.second <<
        //"]\n";
    return y * _dims.first + x;
  }

  bool Map::insert(const std::pair<float, float>& behavior, const std::shared_ptr<Genome> genome) {
    // Extract index of new genome
    const auto idx = this->index(behavior);
    if(_storage[idx] != nullptr) {
      // There is a genome at the given behavior
      if(_storage[idx]->fitness < genome->fitness) {
        // The new genome is better, insert it!
        _storage[idx] = genome;
        return true;
      } else {
        // The old genome is better
        return false;
      }
    } else {
      // There was no genome present in the map for the given behavior so we can
      // insert with confidence
      _storage[idx] = genome;
      return true;
    }
  }

  const std::shared_ptr<Genome> Map::get(const std::pair<float, float>& behavior) const {
    return _storage[index(behavior)];
  }

  const std::vector<std::shared_ptr<Genome>> Map::elements() const {
    std::vector<std::shared_ptr<Genome>> result;
    // Simply iterate underlying storage, if element is not 'nullptr' it should
    // be a valid genome
    for(size_t i = 0; i < _storage.size(); ++i) {
      if(_storage[i] != nullptr) {
        result.push_back(_storage[i]);
      }
    }
    return result;
  }

  size_t Map::size() const {
    size_t num = 0;
    for(size_t i = 0; i < _storage.size(); ++i) {
      if(_storage[i] != nullptr) {
        num += 1;
      }
    }
    return num;
  }

  float Map::coverage() const {
    const float total = static_cast<float>(_dims.first * _dims.second);
    const float size = static_cast<float>(this->size());
    return size / total;
  }

  float Map::precision() const {
    float size = 0;
    float sum = 0.0;
    for(size_t i = 0; i < _storage.size(); ++i) {
      const auto& val = _storage[i];
      if(val != nullptr) {
        sum += val->fitness;
        size += 1;
      }
    }
    if(size > 0.0) {
      return sum / size;
    } else {
      return 0.0;
    }
  }

  float Map::reliability() const {
    const float total = static_cast<float>(_dims.first * _dims.second);
    float sum = 0.0;
    for(size_t i = 0; i < _storage.size(); ++i) {
      const auto& val = _storage[i];
      if(val != nullptr) {
        sum += val->fitness;
      }
    }
    return sum / total;
  }

  std::ostream& operator<<(std::ostream& os, const Map& m) {
    // Output Map in CSV format, one solution per line
    os << "x,y,fitness" << std::endl;
    for(size_t x = 0; x < m._dims.first; ++x) {
      for(size_t y = 0; y < m._dims.second; ++y) {
        const auto index = y * m._dims.first + x;
        const auto& val = m._storage[index];
        float fitness = -1;
        if(val != nullptr) {
          fitness = val->fitness;
        }
        os << x << "," << y << "," << fitness << std::endl;
      }
    }
    return os;
  }
}
