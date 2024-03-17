//
// Created by Anatta Feng on 2024/1/25.
//

#pragma once
#include "ResourceProxy.h"
#include "core/DataProvider.h"
#include "gpu/GpuBuffer.h"

namespace vgfx {

class GpuBufferProxy : public ResourceProxy {
 public:
  /**
   * Creates a GpuBufferProxy from the given data.
   */
  static std::shared_ptr<GpuBufferProxy> MakeFrom(Context* context, std::shared_ptr<Data> data,
                                                  BufferType bufferType);
  /**
   * Creates a GpuBufferProxy from the given data provider.
   */
  static std::shared_ptr<GpuBufferProxy> MakeFrom(Context* context,
                                                  std::shared_ptr<DataProvider> dataProvider,
                                                  BufferType bufferType);

  /**
   * Returns the type of the buffer.
   */
  BufferType bufferType() const {
    return _bufferType;
  }

  /**
   * Returns the associated GpuBuffer instance.
   */
  std::shared_ptr<GpuBuffer> getBuffer() const;

 private:
  BufferType _bufferType = BufferType::Vertex;
  size_t _size = 0;

  GpuBufferProxy(UniqueKey uniqueKey, BufferType bufferType);

  friend class ProxyProvider;
};

} // vgfx