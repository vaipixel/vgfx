//
// Created by Anatta Feng on 2024/3/13.
//

#pragma once

#include "ShaderBuilder.h"
namespace vgfx {

class FragmentShaderBuilder : public ShaderBuilder {
 public:
  explicit FragmentShaderBuilder(ProgramBuilder *program);

  virtual std::string dstColor() = 0;

  void onBeforeChildProcEmitCode(const FragmentProcessor *child);

  void onAfterChildProcEmitCode();

  void declareCustomOutputColor();

 protected:
  virtual std::string colorOutputName() = 0;

  static std::string CustomColorOutputName() {
    return "vgfx_FragColor";
  }

  void onFinalize() override;

};

} // vgfx