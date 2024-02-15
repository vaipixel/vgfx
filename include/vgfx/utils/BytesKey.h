//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
namespace vgfx {
/**
 * A key used for hashing a byte stream.
 */
class BytesKey {
 public:
  bool isValid() const {
    return !values.empty();
  }

  bool write(uint32_t value);

  void write(const void *value);

  void write(const uint8_t value[4]);

  void write(float value);

  friend bool operator==(const BytesKey &a, const BytesKey &b) {
    return a.values == b.values;
  }

  bool operator<(const BytesKey &key) const {
    return values < key.values;
  }

 private:
  std::vector<uint32_t> values = {};

};

struct BytesKeyHasher {
  size_t operator()(const BytesKey &key) const;
};

template<typename T>
using BytesKeyMap = std::unordered_map<BytesKey, T, BytesKeyHasher>;

} // vgfx