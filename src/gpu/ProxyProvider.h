//
// Created by Anatta Feng on 2024/1/22.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "gpu/proxies/GpuBufferProxy.h"

namespace vgfx {

    /**
     * A factory for creating proxy-derived objects.
     */
    class ProxyProvider {
    public:
        explicit ProxyProvider(Context *context);

        bool hasResourceProxy(const ResourceKey &resourceKey);

        std::shared_ptr<GpuBufferProxy> createGpuBufferProxy(const ResourceKey &resourceKey,
                                                             std::shared_ptr<Data> data,
                                                             BufferType bufferType,
                                                             uint32_t renderFlags = 0);
    };

} // vgfx