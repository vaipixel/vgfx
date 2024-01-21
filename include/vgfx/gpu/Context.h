//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include "Device.h"
#include "gpu/ProgramCache.h"
#include "gpu/ResourceCache.h"
#include "gpu/DrawingManager.h"
#include "gpu/ResourceProvider.h"
#include "gpu/ProxyProvider.h"
#include <cstddef>

namespace vgfx {
    class DrawingManager;
    class Device;

    class Context {
    public:
        virtual ~Context();

        /**
         * Return the associated device.
         * @return
         */
        Device *device() const {
            return _device;
        }

        ProgramCache *programCache() const {
            return _programCache;
        }

        ResourceCache *resourceCache() const {
            return _resourceCache;
        }

        DrawingManager *drawingManager() const {
            return _drawingManager;
        }

        ResourceProvider *resourceProvider() const {
            return _resourceProvider;
        }

        ProxyProvider *proxyProvider() const {
            return _proxyProvider;
        }

        /**
         * Return the number if bytes consumed by internal gpu cache.
         * @return
         */
        size_t memoryUsage() const;

        size_t purgeableBytes() const;

        size_t cacheLimit() const;

        void setCacheLimit(size_t bytesLimit);


        bool wait();


    protected:
        explicit Context(Device *device);

    private:
        Device *_device = nullptr;
        ProgramCache *_programCache = nullptr;
        ResourceCache *_resourceCache = nullptr;
        DrawingManager *_drawingManager = nullptr;
        ResourceProvider *_resourceProvider = nullptr;
        ProxyProvider *_proxyProvider = nullptr;

        void releaseAll(bool releaseGPU);

        friend class Device;
    };

} // vgfx