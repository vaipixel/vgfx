//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "vgfx/utils/BytesKey.h"
namespace vgfx {
/**
 * The base class for GPU program. Overrides the onReleaseGPU() method to free all GPU resources.
 * No backend API calls should be made during destructuring since there may be no GPU context that
 * is current on the calling thread.
 */
class Program {
 public:
  explicit Program(Context* context): context(context) {

  }

  virtual ~Program() = default;

  Context* getContext() const {
    return context;
  }
 protected:
  Context *context = nullptr;

  /**
   * Overridden to free GPU resources in the backend API.
   */
  virtual void onReleaseGPU() = 0;
 private:
  BytesKey uniqueKey = {};

};

} // vgfx