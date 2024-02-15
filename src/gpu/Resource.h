//
// Created by Anatta Feng on 2024/1/15.
//

#pragma once

#include <list>
#include "gpu/ResourceKey.h"
#include "vgfx/utils/BytesKey.h"

namespace vgfx {
/**
 * The base class for GPU resource. Overriders the onReleaseGPU() method to free all GPU resources.
 * No backend API calls should be made during destructuring since there may be no GPU context that
 * is current on the calling thread. Note: Resource is not thread safe, do not assess any properties
 * of a Resource unless its associated device is locked.
 */
class Resource {
 public:

  /**
   * A convenient method to add a resource to the cache.
   */
  template<class T>
  static std::shared_ptr<T> AddToCache(Context *context, T *resource,
                                       const BytesKey &recycleKey = {}) {
    return std::static_pointer_cast<T>(context->resourceCache()->addResource(resource, recycleKey));
  }
 protected:
  Context *context = nullptr;

  /**
   * Overridden to free GPU resources in the backend API.
   */
  virtual void onReleaseGPU() = 0;
 private:
  std::shared_ptr<Resource> reference;
  BytesKey recycleKey = {};
  ResourceKey resourceKey = {};
  std::list<Resource *> *cachedList = nullptr;
  std::list<Resource *>::iterator cachedPosition;
  std::chrono::steady_clock::time_point lastUsedTime = {};

  virtual bool isPurgeable() const {
    return reference.use_count() <= 1 && resourceKey.strongCount() == 0;
  }

  bool hasExternalReferences() const {
    return resourceKey.useCount() > 1;
  }

  void release(bool releaseGPU);

};
}