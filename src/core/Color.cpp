//
// Created by Anatta Feng on 2024/1/17.
//

#include "vgfx/core/Color.h"

namespace vgfx {
const const Color &Color::Transparent() {
  static const Color color = {0.0f, 0.0f, 0.0f, 0.0f};
  return color;
}
} // vgfx