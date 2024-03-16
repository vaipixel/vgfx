//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "gpu/ResourceKey.h"
#include "gpu/ResourceHandle.h"

namespace vgfx {

/**
 * The base class for all proxy-derived objects. It defers the acquisition of resources until they
 * are actually required.
 */
class ResourceProxy {
 public:
  virtual ~ResourceProxy() = default;

  /**
   * Retrieves the context associated with this ResourceProxy.
   */
  Context* getContext() const {
    return context;
  }

  /**
   * Returns the UniqueKey associated with this ResourceProxy.
   */
  const UniqueKey& getUniqueKey() const {
    return handle.key();
  }

 protected:
  Context* context = nullptr;
  ResourceHandle handle = {};

  explicit ResourceProxy(UniqueKey uniqueKey) : handle(std::move(uniqueKey)) {
  }

  friend class ProxyProvider;
};
}
