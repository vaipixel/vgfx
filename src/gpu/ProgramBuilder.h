//
// Created by Anatta Feng on 2024/3/12.
//

#pragma once

#include "gpu/processors/Processor.h"
#include "ShaderVar.h"
namespace vgfx {

class ProgramBuilder {
 private:
  std::vector<const Processor *> currentProcessors = {};
  std::vector<ShaderVar> transformedCoordVars = {};

  /**
   * Generates a possibly mangled name for a stage variable and writes it to the fragment shader.
   */
  void nameExpression(std::string *output, const std::string &baseName);
};

} // vgfx