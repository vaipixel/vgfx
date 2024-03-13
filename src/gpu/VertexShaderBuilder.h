//
// Created by Anatta Feng on 2024/3/13.
//

#pragma once

#include "ShaderBuilder.h"
namespace vgfx {
static const std::string RTAdjustName = "vgfx_RTAdjust";

class VertexShaderBuilder : public ShaderBuilder {
 public:
  explicit VertexShaderBuilder(ProgramBuilder *program) : ShaderBuilder(program) {
  }

  virtual void emitNormalizedPosition(const std::string &devPos) = 0;

 private:
  void onFinalize() override;
};

} // vgfx