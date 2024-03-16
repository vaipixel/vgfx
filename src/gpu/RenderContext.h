//
// Created by Anatta Feng on 2024/3/16.
//

#pragma once

#include "gpu/proxies/RenderTargetProxy.h"
#include "gpu/processors/FragmentProcessor.h"
#include "gpu/ops/Op.h"
namespace vgfx {

class RenderContext {
 public:
  explicit RenderContext(std::shared_ptr<RenderTargetProxy> renderTargetProxy)
      : renderTargetProxy(renderTargetProxy) {
  }

  void fillWithFP(std::unique_ptr<FragmentProcessor> fp, const Matrix &localMatrix,
                  bool autoResolve = false);

  void fillRectWithFP(const Rect &dstRect, std::unique_ptr<FragmentProcessor> fp,
                      const Matrix &localMatrix);

  void addOp(std::unique_ptr<Op> op);
 private:
  std::shared_ptr<RenderTargetProxy> renderTargetProxy = nullptr;
  std::shared_ptr<OpsRenderTask> opsTask = nullptr;
};

} // vgfx