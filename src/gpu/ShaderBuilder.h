//
// Created by Anatta Feng on 2024/3/12.
//

#pragma once

#include "ShaderVar.h"
#include "ProgramBuilder.h"

namespace vgfx {

/**
 * Features that should only be enabled internally by the builders.
 */
enum class PrivateFeature : unsigned {
  None = 0,
  OESTexture = 1 << 0,
  FramebufferFetch = 1 << 1,
  VGFX_MARK_AS_BITMASK_ENUM(FramebufferFetch)
};

class ShaderBuilder {

 protected:
  class Type {
   public:
    static const uint8_t VersionDecl = 0;
    static const uint8_t Extensions = 1;
    static const uint8_t Definitions = 2;
    static const uint8_t PrecisionQualifier = 3;
    static const uint8_t Uniforms = 4;
    static const uint8_t Inputs = 5;
    static const uint8_t Outputs = 6;
    static const uint8_t Functions = 7;
    static const uint8_t Main = 8;
    static const uint8_t Code = 9;
  };

  /**
   * A general function which enables an extension in a shader if the feature bit is not present
   */
  void addFeature(PrivateFeature featureBit, const std::string &extensionName);

  virtual void onFinalize() = 0;

  void appendEnterIfNotEmpty(uint8_t type);

  void appendIndentationIfNeeded(const std::string &code);

  std::string getDeclarations(const std::vector<ShaderVar> &vars, ShaderFlags flag) const;

  std::vector<std::string> shaderStrings;
  ProgramBuilder *programBuilder = nullptr;
  std::vector<ShaderVar> inputs;
  std::vector<ShaderVar> outputs;
  PrivateFeature featureAddedMask = PrivateFeature::None;
  bool finalized = false;
  int indentation = 0;
  bool atLineStart = false;
};

} // vgfx