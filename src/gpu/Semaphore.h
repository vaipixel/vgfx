//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <memory>
#include "vgfx/gpu/Backend.h"
namespace vgfx {

/**
 * Wrapper class for a backend semaphore object.
 */
class Semaphore {
 public:
  static std::unique_ptr<Semaphore> Wrap(const BackendSemaphore *backendSemaphore);

  virtual ~Semaphore() = default;

  virtual BackendSemaphore getBackendSemaphore() const = 0;

};

} // vgfx