//
// Created by Anatta Feng on 2024/3/16.
//

#pragma once

#include "ResourceKey.h"
namespace vgfx {

/**
 * ResourceHandle holds a strong reference to the associated resource. When a resource is referenced
 * by a ResourceHandle, the Context ensures that the resource is not destroyed until all instances
 * of ResourceHandle are released or the Context itself is destroyed.
 */
class ResourceHandle {
 public:
  /**
   * Creates an empty ResourceHandle.
   */
  ResourceHandle() = default;

  explicit ResourceHandle(const UniqueKey &key);

  explicit ResourceHandle(UniqueKey &&key) noexcept;

  ResourceHandle(const ResourceHandle &key);

  ResourceHandle(ResourceHandle &&key) noexcept;

  virtual ~ResourceHandle();

  /**
   * Returns the UniqueKey associated with the ResourceHandle.
   */
  const UniqueKey &key() const {
    return uniqueKey;
  }

  /**
   * Returns true if the ResourceHandle is empty.
   */
  bool empty() const {
    return uniqueKey.empty();
  }

  /**
   * Returns the total number of times the domain has been referenced.
   */
  long useCount() const {
    return uniqueKey.useCount();
  }

  /**
   * Returns the number of times the domain has been strongly referenced.
   */
  long strongCount() const {
    return uniqueKey.strongCount();
  }

  ResourceHandle &operator=(const UniqueKey &key);

  ResourceHandle &operator=(UniqueKey &&key) noexcept;

  ResourceHandle &operator=(const ResourceHandle &handle);

  ResourceHandle &operator=(ResourceHandle &&handle) noexcept;

  bool operator==(const ResourceHandle &handle) const;

  bool operator!=(const ResourceHandle &handle) const;

 private:
  UniqueKey uniqueKey = {};
};

} // vgfx