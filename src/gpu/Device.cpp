//
// Created by Anatta Feng on 2024/1/7.
//

#include "vgfx/gpu/Device.h"
#include "utils/UniqueID.h"
#include "utils/Logger.h"
#include "vgfx/gpu/Context.h"


namespace vgfx {
Device::Device() : _uniqueID(UniqueID::Next()) {
}

Device::~Device() {
  DEBUG_ASSERT(context == nullptr);
}

Context *Device::lockContext() {
  locker.lock();
  contextLocked = onLockContext();
  if (!contextLocked) {
    locker.unlock();
    return nullptr;
  }
  return context;
}

void Device::unlock() {
  if (contextLocked) {
    contextLocked = false;
    onUnlockContext();
  }
  locker.unlock();
}

void Device::releaseAll() {
  std::lock_guard<std::mutex> autoLock(locker);
  if (context == nullptr) {
    LOGD("Context is nullptr");
    return;
  }
  contextLocked = onLockContext();
  context->releaseAll(contextLocked);
  if (contextLocked) {
    contextLocked = false;
    onUnlockContext();
  }
  delete context;
  context = nullptr;
}

bool Device::onLockContext() {
  return context != nullptr;
}

void Device::onUnlockContext() {

}
} // vgfx