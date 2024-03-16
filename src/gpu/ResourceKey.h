//
// Created by Anatta Feng on 2024/1/22.
//

#pragma once

#include <atomic>
#include <cstring>
#include <memory>
#include "vgfx/utils/BytesKey.h"

namespace vgfx {
class UniqueDomain;

/**
 * ResourceKey allows a code path to create cached resources for which it is the exclusive user.
 * The code path generates a unique domain which it sets on its keys. This guarantees that there are
 * no cross-domain collisions. When a resource is only referenced by ResourceKeys, it falls under
 * the management of the Context and can be destroyed at any time. To maintain a strong reference to
 * the resource, use the ResourceHandle class. For further details on the differences between
 * ResourceKeys and recycle keys, please refer to the comments in Resource::getResourceKey() and
 * Resource::getRecycleKey().
 */
class ResourceKey {
 public:
  virtual ~ResourceKey();

  /**
   * Returns true if the resource key is empty.
   */
  bool empty() const {
    return data == nullptr;
  }

  /**
   * Returns the hash of the key. This is used to quickly compare keys.
   */
  size_t hash() const {
    return data == nullptr ? 0 : data[0];
  }
 protected:
  ResourceKey() = default;
  ResourceKey(uint32_t *data, size_t count);
  ResourceKey(const ResourceKey &that);
  ResourceKey(ResourceKey &&key) noexcept;
  bool equal(const ResourceKey &that) const;
  void copy(const ResourceKey &that);
  uint32_t *data = nullptr;
  size_t count = 0;

};

/**
 * A key used for scratch resources. There are three important rules about scratch keys:
 *
 *    1) Multiple resources can share the same scratch key. Therefore, resources assigned the same
 *       scratch key should be interchangeable with respect to the code that uses them.
 *    2) A resource can have at most one scratch key, and it is set at resource creation by the
 *       resource itself.
 *    3) When a scratch resource is referenced, it will not be returned from the cache for a
 *       subsequent cache request until all references are released.
 */
class ScratchKey : public ResourceKey {
 public:
  /**
   * Creates an empty ScratchKey.
   */
  ScratchKey() = default;

  ScratchKey(const ScratchKey &that) : ResourceKey(that) {
  }

  ScratchKey(ScratchKey &&that) noexcept: ResourceKey(std::move(that)) {
  }

  ScratchKey(const BytesKey &that) {
    *this = that;
  }

  ScratchKey &operator=(const ScratchKey &that) {
    copy(that);
    return *this;
  }

  ScratchKey &operator=(const BytesKey &that);

  bool operator==(const ScratchKey &that) const {
    return equal(that);
  }

  bool operator!=(const ScratchKey &that) const {
    return !equal(that);
  }

 private:
  ScratchKey(uint32_t *data, size_t count);
};

struct ScratchKeyHasher {
  size_t operator()(const ScratchKey &scratchKey) const {
    return scratchKey.hash();
  }
};

template<typename T>
using ScratchKeyMap = std::unordered_map<ScratchKey, T, ScratchKeyHasher>;

class UniqueDomain;

/**
 * A key that allows for exclusive use of a resource for a use case (AKA "domain"). There are three
 * rules governing the use of unique keys:
 *
 *    1) Only one resource can have a given unique key at a time. Hence, "unique".
 *    2) A resource can have at most one unique key at a time.
 *    3) Unlike scratch keys, multiple requests for a unique key will return the same resource even
 *       if the resource already has references.
 *
 * This key type allows a code path to create cached resources for which it is the exclusive user.
 * The code path creates a domain which it sets on its keys. This guarantees that there are no
 * cross-domain collisions. Unique keys preempt scratch keys. While a resource has a unique key, it
 * is inaccessible via its scratch key. It can become scratch again if the unique key is removed or
 * no longer has any external references.
 */
class UniqueKey : public ResourceKey {
 public:
  /**
   * Creates a new UniqueKey with a valid domain.
   */
  static UniqueKey Make();

  /**
   * Creates a new UniqueKey by combining an existing UniqueKey and a BytesKey. The returned
   * UniqueKey will share the same unique domain as the original UniqueKey.
   */
  static UniqueKey Combine(const UniqueKey &uniqueKey, const BytesKey &bytesKey);

  /**
   * Creates an empty UniqueKey.
   */
  UniqueKey() = default;

  UniqueKey(const UniqueKey &key);

  UniqueKey(UniqueKey &&key) noexcept;

  virtual ~UniqueKey();

  /**
   * Returns the domain ID of the unique key.
   */
  uint32_t domainID() const;

  /**
   * Returns the total number of times the domain has been referenced.
   */
  long useCount() const;

  /**
   * Returns the number of times the domain has been strongly referenced.
   */
  long strongCount() const;

  UniqueKey &operator=(const UniqueKey &key);

  UniqueKey &operator=(UniqueKey &&key) noexcept;

  bool operator==(const UniqueKey &that) const {
    return equal(that);
  }

  bool operator!=(const UniqueKey &that) const {
    return !equal(that);
  }

 private:
  UniqueDomain *uniqueDomain = nullptr;

  explicit UniqueKey(UniqueDomain *domain);

  UniqueKey(uint32_t *data, size_t count, UniqueDomain *domain);

  void addStrong();

  void releaseStrong();

  friend class ResourceHandle;
  friend class LazyUniqueKey;
};

struct UniqueKeyHasher {
  size_t operator()(const UniqueKey& uniqueKey) const {
    return uniqueKey.hash();
  }
};

template <typename T>
using UniqueKeyMap = std::unordered_map<UniqueKey, T, UniqueKeyHasher>;

/**
 * LazyUniqueKey defers the acquisition of the UniqueKey until it is actually needed.
 */
class LazyUniqueKey {
 public:
  ~LazyUniqueKey();

  /**
   * Returns the associated UniqueKey. If the UniqueKey is empty, it will create a new one
   * immediately. Calling this method from multiple threads will not create multiple UniqueKeys.
   * This method is thread-safe as long as there is no concurrent reset() call.
   */
  UniqueKey get();

  /**
   * Resets the LazyUniqueKey to an empty state. This method is not thread-safe.
   */
  void reset();

 private:
  std::atomic<UniqueDomain*> uniqueDomain = nullptr;
};

}