//
// Created by Anatta Feng on 2024/2/15.
//

#include <atomic>
#include "Op.h"

namespace vgfx {
uint8_t Op::GenOpClassID() {
  static std::atomic_uint8_t currentOpClassID = {1};
  return currentOpClassID.fetch_add(1, std::memory_order_relaxed);
}

Op::comb
} // vgfx