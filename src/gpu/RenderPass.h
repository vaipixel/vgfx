//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <optional>
#include "Blend.h"
#include "Program.h"
#include "gpu/ProgramInfo.h"
#include "gpu/RenderTarget.h"
#include "gpu/processors/GeometryProcessor.h"
#include "gpu/proxies/GpuBufferProxy.h"
#include "gpu/proxies/RenderTargetProxy.h"
#include "vgfx/core/BlendMode.h"
#include "vgfx/core/Color.h"
#include "vgfx/gpu/Context.h"

namespace vgfx {
/**
 * Geometric primitives used for drawing.
 */
enum class PrimitiveType {
  Triangles,
  TriangleStrip,
};

class RenderPass {
 public:
  virtual ~RenderPass() = default;

  Context *getContext() {
    return context;
  }

  std::shared_ptr<RenderTarget> renderTarget() {
    return _renderTarget;
  }

  std::shared_ptr<Texture> renderTargetTexture() {
    return _renderTargetTexture;
  }

  bool begin(std::shared_ptr<RenderTargetProxy> renderTargetProxy);
  void end();
  void bindProgramAndScissorClip(const ProgramInfo *programInfo, const Rect &drawBounds);
  void bindBuffers(std::shared_ptr<GpuBuffer> indexBuffer, std::shared_ptr<GpuBuffer> vertexBuffer);
  void draw(PrimitiveType primitiveType, size_t baseVertex, size_t vertexCount);
  void drawIndexed(PrimitiveType primitiveType, size_t baseIndex, size_t indexCount);
  void clear(const Rect &scissor, Color color);

 protected:
  explicit RenderPass(Context *context) : context(context) {
  }

  virtual bool onBindProgramAndScissorClip(const ProgramInfo *programInfo,
                                           const Rect &drawBounds) = 0;
  virtual void onBindBuffers(std::shared_ptr<GpuBuffer> indexBuffer,
                             std::shared_ptr<GpuBuffer> vertexBuffer) = 0;
  virtual void onDraw(PrimitiveType primitiveType, size_t baseVertex, size_t vertexCount) = 0;
  virtual void onDrawIndexed(PrimitiveType primitiveType, size_t baseIndex, size_t indexCount) = 0;
  virtual void onClear(const Rect &scissor, Color color) = 0;

  Context *context = nullptr;
  std::shared_ptr<RenderTarget> _renderTarget = nullptr;
  std::shared_ptr<Texture> _renderTargetTexture = nullptr;
  Program *_program = nullptr;
  std::shared_ptr<GpuBuffer> _indexBuffer;
  std::shared_ptr<GpuBuffer> _vertexBuffer;

 private:
  enum class DrawPipelineStatus { Ok = 0, NotConfigured, FailedToBind };

  void resetActiveBuffers();

  DrawPipelineStatus drawPipelineStatus = DrawPipelineStatus::NotConfigured;
};

} // vgfx