//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <cstddef>
#include <memory>
#include "gpu/Resource.h"
#include "vgfx/gpu/Context.h"
namespace vgfx {

enum class BufferType {
  Index,
  Vertex,
};

class GpuBuffer : public Resource {
 public:
  static std::shared_ptr<GpuBuffer> Make(Context *context, const void *buffer, size_t size,
                                         BufferType bufferType);

  BufferType bufferType() const {
    return _bufferType;
  }

  size_t size() const {
    return _sizeInBytes;
  }

  size_t memoryUsage() const override {
    return _sizeInBytes;
  }

 protected:
  GpuBuffer(BufferType bufferType, size_t sizeInBytes)
      : _bufferType(bufferType), _sizeInBytes(sizeInBytes) {
  }

  BufferType _bufferType;
 private:
  size_t _sizeInBytes;
};

} // vgfx