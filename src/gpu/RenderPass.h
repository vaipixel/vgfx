//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "gpu/Program.h"
#include "gpu/GpuBuffer.h"
namespace vgfx {
/**
 * Geometric primitives used for drawing.
 */
enum class PrimitiveType {
  Triangles,
  TriangleStrip
};

class RenderPass {
 public:
  virtual ~RenderPass() = default;

 protected:
  explicit RenderPass(Context* context) {

  }

  Context *context = nullptr;
  std::shared_ptr<RenderTarget> _renderTarget = nullptr;
  std::shared_ptr<Texture> _renderTargetTexture = nullptr;
  Program* _program = nullptr;
  std::shared_ptr<GpuBuffer> _indexBuffer;
  std::shared_ptr<GpuBuffer> _vertexBuffer;

 private:
  enum class DrawPipelineStatus { Ok = 0, NotConfigured, FailedToBind };
  void resetActiveBuffers();
  DrawPipelineStatus drawPiplineStatus = DrawPipelineStatus::NotConfigured;
};

} // vgfx