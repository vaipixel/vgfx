//
// Created by Anatta Feng on 2024/2/25.
//

#pragma once

#include "gpu/processors/FragmentProcessor.h"
namespace vgfx {

class AARectEffect : public FragmentProcessor {
 public:
  static std::unique_ptr<AARectEffect> Make(const Rect &rect);
  std::string name() const override {
    return "AARectEffect";
  }
};

} // vgfx