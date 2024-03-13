//
// Created by Anatta Feng on 2024/3/13.
//

#pragma once

#include "TextureSampler.h"
#include "SamplerHandle.h"
#include "ShaderVar.h"
#include "ProgramBuilder.h"
namespace vgfx {

class UniformHandler {
 public:
  virtual ~UniformHandler() = default;

  /**
   * Adds a uniform variable to the current program, that has visibility in one or more shaders.
   * visibility is a bitfield of ShaderFlag values indicating from which shaders the uniform should
   * be accessible. At least one bit must be set. The actual uniform name will be mangled. Returns
   * the final uniform name.
   */
  std::string addUniform(ShaderFlags visibility, ShaderLanguageType type, const std::string &name) {
    return internalAddUniform(visibility, type, name);
  }

  /**
   * Adds a sampler to the current program.
   */
  SamplerHandle addSampler(const TextureSampler *sampler, const std::string &name);

 protected:
  explicit UniformHandler(ProgramBuilder *program) : programBuilder(program) {
  }

  ProgramBuilder *programBuilder;
 private:
  std::unordered_map<const TextureSampler *, SamplerHandle> samplerMap = {};
  virtual const ShaderVar &samplerVariable(SamplerHandle samplerHandle) const = 0;

  virtual const Swizzle &samplerSwizzle(SamplerHandle samplerHandle) const = 0;

  virtual std::string internalAddUniform(ShaderFlags visibility, ShaderLanguageType type,
                                         const std::string &name) = 0;

  virtual SamplerHandle internalAddSampler(const TextureSampler *sampler,
                                           const std::string &name) = 0;

  virtual std::string getUniformDeclarations(ShaderFlags visibility) const = 0;

  friend class ProgramBuilder;
};

} // vgfx