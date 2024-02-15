//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "gpu/TextureSampler.h"
#include "gpu/RenderPass.h"
#include "gpu/Semaphore.h"
namespace vgfx {

class Gpu {
 public:
  virtual ~Gpu() = default;

  Context* getContext() {
    return context;
  }

  virtual std::shared_ptr<RenderPass> getRenderPass() = 0;

  virtual std::unique_ptr<TextureSampler> createSampler(int width, int height, PixelFormat format,
                                                        int mipLevelCount = 0);

  virtual void deleteSampler(TextureSampler *sampler) = 0;

  virtual void writePixels(const TextureSampler *sampler, Rect rect, const void *pixels,
                           size_t rowBytes) = 0;

  virtual void resolveRenderTarget(RenderTarget *renderTarget) = 0;

  virtual bool insertSemaphore(Semaphore *semaphore) = 0;

  virtual bool waitSemaphore(const Semaphore *semaphore) = 0;

  virtual bool submitToGpu(bool syncCpu) = 0;

  virtual void submit(RenderPass *renderPass) = 0;

  void regenerateMipmapLevels(const TextureSampler *sampler);

 protected:
  Context* context;

  explicit Gpu(Context* context) : context(context) {
  }

  virtual void onRegenerateMipmapLevels(const TextureSampler *sampler) = 0;
};

} // vgfx