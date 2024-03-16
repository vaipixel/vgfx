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
  BytesKey() = default;

  /**
   * Creates a key with the given capacity of uint32_t values.
   */
  explicit BytesKey(size_t capacity) {
    values.reserve(capacity);
  }

  /**
   * Reserves the capacity of uint32_t values.
   */
  void reserve(size_t capacity) {
    values.reserve(capacity);
  }

  /**
   * Returns true if this key is valid.
   */
  bool isValid() const {
    return !values.empty();
  }

  /**
   * Writes an uint32 value into the key.
   */
  bool write(uint32_t value);

  /**
   * Writes an int value into the key.
   */
  void write(int value);

  /**
   * Writes a pointer value into the key.
   */
  void write(const void *value);

  /**
   * Writes an uint32 value into the key.
   */
  void write(const uint8_t value[4]);

  /**
   * Writes a float value into the key.
   */
  void write(float value);

  /**
   * Pointer to the key data
   */
  const uint32_t* data() const {
    return values.data();
  }

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