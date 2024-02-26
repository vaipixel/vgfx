//
// Created by Anatta Feng on 2024/2/6.
//

#pragma once

#include <cstdint>
#include <string>
#include "vgfx/gpu/Context.h"
namespace vgfx {
#define DEFINE_PROCESSOR_CLASS_ID               \
  static uint32_t ClassID() {                   \
    static uint32_t ClassID = UniqueID::Next(); \
    return ClassID;                             \
  }

class Processor {
 public:
  explicit Processor(uint32_t classID): _classID(classID) {
  }

  virtual ~Processor() = default;

  /**
   * Human-meaningful string to identify this processor.
   */
  virtual std::string name() const = 0;

  uint32_t classID() const {
    return _classID;
  }

  virtual void computeProcessorKey(Context *context, BytesKey *bytesKey) const = 0;
 private:
  uint32_t _classID = 0;
};
}
