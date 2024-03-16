//
// Created by Anatta Feng on 2024/3/12.
//

#pragma once

#include "gpu/processors/Processor.h"
#include "ShaderVar.h"
#include "gpu/processors/FragmentProcessor.h"
#include "SamplerHandle.h"
#include "gpu/FragmentShaderBuilder.h"
#include "VertexShaderBuilder.h"
#include "VaryingHandler.h"
#include "UniformHandler.h"
namespace vgfx {

class ProgramBuilder {
 public:
  static std::unique_ptr<Program> CreateProgram(Context *context, const Pipeline *pipeline);

  virtual ~ProgramBuilder() = default;

  Context* getContext() const {
    return context;
  }

  const Pipeline* getPipeline() const {
    return pipeline;
  }

  virtual std::string versionDeclString() = 0;

  virtual std::string textureFuncName() const = 0;

  virtual std::string getShaderVarDeclarations(const ShaderVar &var, ShaderFlags flags) const = 0;

  std::string getUniformDeclarations(ShaderFlags visibility) const;

  const ShaderVar& samplerVariable(SamplerHandle handle) const {
    return uniformHandler()->samplerVariable(handle);
  }

  Swizzle samplerSwizzle(SamplerHandle handle) const {
    return uniformHandler()->samplerSwizzle(handle);
  }

  std::string nameVariable(const std::string &name) const;

  virtual UniformHandler *uniformHandler() = 0;

  virtual const UniformHandler *uniformHandler() const = 0;

  virtual VaryingHandler *varyingHandler() = 0;

  virtual VertexShaderBuilder *vertexShaderBuilder() = 0;

  virtual FragmentShaderBuilder *fragmentShaderBuilder() = 0;

 protected:
  Context *context = nullptr;
  const Pipeline *pipeline = nullptr;
  int numFragmentSamplers = 0;

  ProgramBuilder(Context *context, const Pipeline *pipeline);

  bool emitAndInstallProcessors();

  void finalizeShaders();

  virtual bool checkSamplerCounts() = 0;
 private:
  std::vector<const Processor *> currentProcessors = {};
  std::vector<ShaderVar> transformedCoordVars = {};

  /**
   * Generates a possibly mangled name for a stage variable and writes it to the fragment shader.
   */
  void nameExpression(std::string *output, const std::string &baseName);

  void emitAndInstallGeoProc(std::string *outputColor, std::string *outputCoverage);

  void emitAndInstallFragProcessors(std::string *color, std::string *coverage);

  std::string emitAndInstallFragProc(const FragmentProcessor *processor,
                                     size_t transformedCoordVarsIndex, const std::string &input);

  void emitAndInstallXferProc(const std::string &colorIn, const std::string &coverageIn);

  SamplerHandle emitSampler(const TextureSampler *sampler, const std::string &name);

  void emitFSOutputSwizzle();

  friend class FragmentShaderBuilder;
  friend class ProcessorGuard;
};

} // vgfx