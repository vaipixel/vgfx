//
// Created by Anatta Feng on 2024/1/15.
//

#pragma once

#include "gpu/ResourceKey.h"
#include "gpu/ResourceCache.h"
#include "vgfx/gpu/Context.h"

namespace vgfx {
class Context;

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
                                       const ScratchKey &scratchKey = {}) {
    return std::static_pointer_cast<T>(context->resourceCache()->addResource(resource, scratchKey));
  }

  /**
   * A convenient method to retrieve a unique resource in the cache by the specified UniqueKey.
   */
  template<class T>
  static std::shared_ptr<T> Find(Context *context, const UniqueKey &uniqueKey) {
    return std::static_pointer_cast<T>(context->resourceCache()->findUniqueResource(uniqueKey));
  }

  /**
   * A convenient method to retrieve a scratch resource in the cache by the specified ScratchKey.
   */
  template<class T>
  static std::shared_ptr<T> Find(Context *context, const ScratchKey &scratchKey) {
    return std::static_pointer_cast<T>(context->resourceCache()->findScratchResource(scratchKey));
  }

  virtual ~Resource() = default;

  /**
   * Retrieves the context associated with this Resource.
   */
  Context *getContext() const {
    return context;
  }

  /**
   * Retrieves the amount of GPU memory used by this resource in bytes.
   */
  virtual size_t memoryUsage() const = 0;

  /**
   * Assigns a UniqueKey to the resource. The resource will be findable via this UniqueKey using
   * ResourceCache.findUniqueResource(). This method is not thread safe, call it only when the
   * associated context is locked.
   */
  void assignUniqueKey(const UniqueKey &newKey);

  /*
   * Removes the UniqueKey from the resource. This method is not thread safe, call it only when
   * the associated context is locked.
   */
  void removeUniqueKey();
 protected:
  Context *context = nullptr;

  /**
   * Overridden to free GPU resources in the backend API.
   */
  virtual void onReleaseGPU() = 0;
 private:
  std::shared_ptr<Resource> reference;
  ScratchKey scratchKey = {};
  UniqueKey uniqueKey = {};
  std::list<Resource *> *cachedList = nullptr;
  std::list<Resource *>::iterator cachedPosition;
  std::chrono::steady_clock::time_point lastUsedTime = {};

  virtual bool isPurgeable() const {
    return reference.use_count() <= 1 && uniqueKey.strongCount() == 0;
  }

  bool hasExternalReferences() const {
    return uniqueKey.useCount() > 1;
  }

  void release(bool releaseGPU);

  friend class ResourceCache;
};
}