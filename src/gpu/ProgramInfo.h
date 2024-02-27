//
// Created by Anatta Feng on 2024/2/27.
//

#pragma once

#include "gpu/TextureSampler.h"
#include "gpu/SamplerState.h"
#include "UniformBuffer.h"
namespace vgfx {

struct SamplerInfo {
  const TextureSampler* sampler;
  SamplerState state;
};
/**
 * This immutable object contains information needed to build a shader program and set API state for
 * a draw.
 */
class ProgramInfo {
 public:
  virtual ~ProgramInfo() = default;

  /**
   * Returns true if the draw requires a texture barrier.
   */
  virtual bool requiresBarrier() const = 0;

  /**
   * Returns the blend info for the draw. A nullptr is returned if the draw does not require
   * blending.
   */
  virtual const BlendInfo *blendInfo() const = 0;

  /**
   * Collects uniform data for the draw.
   */
  virtual void getUniforms(UniformBuffer *uniformBuffer) const = 0;

  /**
   * Collects texture samplers for the draw.
   */
  virtual std::vector<SamplerInfo> getSamplers() const = 0;

  /**
   * Computes a unique key for the program.
   */
  virtual void computeProgramKey(Context *context, BytesKey *programKey) const = 0;

  /**
   * Creates a new program.
   */
  virtual std::unique_ptr<Program> createProgram(Context *context) const = 0;
};

} // vgfx