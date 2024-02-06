//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include <mutex>
#include "Context.h"
#include <cstdint>

namespace vgfx {
class Context;

/**
 * The GPU interface for drawing graphics.
 */
class Device {
 public:
  virtual ~Device();

  /**
   * Returns a global unique ID for this device.
   * @return
   */
  uint32_t uniqueID() const {
    return _uniqueID;
  }

  /**
   * Locks the rendering context associated with this device, if another thread has already locked
   * the device by lockContext(), a call to lockContext() will block execution until the device
   * is available. The returned context can be used to draw graphics. A nullptr is returned if the
   * context can not be locked on the calling thread, and leaves the device unlocked.
   * @return
   */
  Context *lockContext();

  /**
   * Unlocks the device. After this method is called all subsequent calls on the previously returned context will be invalid and may lead to runtime crash.
   */
  void unlock();

 protected:
  std::mutex locker = {};
  Context *context = nullptr;
  std::weak_ptr<Device> weakThis;

  Device();

  void releaseAll();

  virtual bool onLockContext();

  virtual void onUnlockContext();

 private:
  uint32_t _uniqueID = 0;
  bool contextLocked = false;
};

} // vgfx

