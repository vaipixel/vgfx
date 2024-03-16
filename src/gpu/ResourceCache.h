//
// Created by Anatta Feng on 2024/1/22.
//

#pragma once
#include <functional>
#include <list>
#include <unordered_map>
#include "gpu/ResourceKey.h"
#include "vgfx/gpu/Context.h"

namespace vgfx {
class Resource;

/**
 * Manages the lifetime of all Resource instances.
 */
class ResourceCache {
 public:
  explicit ResourceCache(Context* context);

  /**
   * Returns true if there is no cache at all.
   */
  bool empty() const;

  /**
   * Returns the number of bytes consumed by resources.
   */
  size_t getResourceBytes() const {
    return totalBytes;
  }

  /**
   * Returns the number of bytes held by purgeable resources.
   */
  size_t getPurgeableBytes() const {
    return purgeableBytes;
  }

  /**
   * Returns current cache limits of max gpu memory byte size.
   */
  size_t cacheLimit() const {
    return maxBytes;
  }

  /**
   * Sets the cache limits of max gpu memory byte size.
   */
  void setCacheLimit(size_t bytesLimit);

  /**
   * Returns a scratch resource in the cache by the specified ScratchKey.
   */
  std::shared_ptr<Resource> findScratchResource(const ScratchKey& scratchKey);

  /**
   * Retrieves a unique resource in the cache by the specified UniqueKey.
   */
  std::shared_ptr<Resource> findUniqueResource(const UniqueKey& uniqueKey);

  /**
   * Returns true if there is a corresponding unique resource for the specified UniqueKey.
   */
  bool hasUniqueResource(const UniqueKey& uniqueKey);

  /**
   * Purges GPU resources that haven't been used since the passed point in time.
   * @param purgeTime A time point previously returned by std::chrono::steady_clock::now().
   * @param scratchResourcesOnly If true, the purgeable resources containing unique keys are spared.
   * If false, then all purgeable resources will be deleted.
   */
  void purgeNotUsedSince(std::chrono::steady_clock::time_point purgeTime,
                         bool scratchResourcesOnly = false);

  /**
   * Purge unreferenced resources from the cache until the provided bytesLimit has been reached,
   * or we have purged all unreferenced resources. Returns true if the total resource bytes is not
   * over the specified bytesLimit after purging.
   * @param bytesLimit The desired number of bytes after puring.
   * @param scratchResourcesOnly If true, the purgeable resources containing unique keys are spared.
   * If false, then all purgeable resources will be deleted.
   */
  bool purgeUntilMemoryTo(size_t bytesLimit, bool scratchResourcesOnly = false);

  /**
   * Purge unreferenced resources not used since the specific time point until the default
   * cacheLimit is reached.
   */
  bool purgeToCacheLimit(std::chrono::steady_clock::time_point notUsedSinceTime);

 private:
  Context* context = nullptr;
  size_t maxBytes = 0;
  size_t totalBytes = 0;
  size_t purgeableBytes = 0;
  std::list<Resource*> nonpurgeableResources = {};
  std::list<Resource*> purgeableResources = {};
  ScratchKeyMap<std::vector<Resource*>> scratchKeyMap = {};
  UniqueKeyMap<Resource*> uniqueKeyMap = {};

  static void AddToList(std::list<Resource*>& list, Resource* resource);
  static void RemoveFromList(std::list<Resource*>& list, Resource* resource);
  static bool InList(const std::list<Resource*>& list, Resource* resource);

  void releaseAll(bool releaseGPU);
  void processUnreferencedResources();
  std::shared_ptr<Resource> addResource(Resource* resource, const ScratchKey& scratchKey);
  std::shared_ptr<Resource> refResource(Resource* resource);
  void removeResource(Resource* resource);
  void purgeResourcesByLRU(bool scratchResourceOnly,
                           const std::function<bool(Resource*)>& satisfied);

  void changeUniqueKey(Resource* resource, const UniqueKey& uniqueKey);
  void removeUniqueKey(Resource* resource);
  Resource* getUniqueResource(const UniqueKey& uniqueKey);

  friend class Resource;
  friend class Context;
};
} // vgfx