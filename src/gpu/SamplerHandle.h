//
// Created by Anatta Feng on 2024/3/12.
//

#pragma once

#include <cstddef>
#include <climits>
namespace vgfx {

class SamplerHandle {
 public:
  SamplerHandle() = default;

  explicit SamplerHandle(size_t value) : value(value) {
  }

  bool isValid() const {
    return value != ULONG_MAX;
  }

  size_t toIndex() const {
    return value;
  }

 private:
  size_t value = ULONG_MAX;
};

} // vgfx