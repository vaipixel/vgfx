//
// Created by Anatta Feng on 2024/1/22.
//

#pragma once

#include <vector>
#include "unordered_map"
#include "vgfx/gpu/Context.h"
#include "gpu/tasks/ResourceTask.h"
#include "gpu/proxies/RenderTask.h"
#include "gpu/tasks/OpsRenderTask.h"
#include "gpu/proxies/RenderTargetProxy.h"
#include "vgfx/core/Rect.h"
#include "vgfx/core/Point.h"

namespace vgfx {

class DrawingManager {

 public:
  explicit DrawingManager(Context *context) : context(context) {

  }

  std::shared_ptr<OpsRenderTask> addOpsTask(std::shared_ptr<RenderTargetProxy> renderTargetProxy);

  void addTextureResolveTask(std::shared_ptr<RenderTargetProxy> renderTargetProxy);

  void addRenderTargetCopyTask(std::shared_ptr<RenderTargetProxy> source,
                               std::shared_ptr<TextureProxy> dest, Rect srcRect, Point dstPoint);

  void addResourceTask(std::shared_ptr<ResourceTask> resourceTask);

  /**
   * Returns true if any render tasks were executed.
   * @return
   */
  bool flush();

 private:
  void closeActiveOpsTask();

  Context *context = nullptr;
  std::unordered_map<uint64_t, ResourceTask *> resourceTaskMap = {};
  std::vector<std::shared_ptr<ResourceTask>> resourceTasks = {};
  std::vector<std::shared_ptr<RenderTask>> renderTasks = {};
  OpsRenderTask *activeOpsTask = nullptr;

};

} // vgfx