//
// Created by 冯旭超 on 2024/1/7.
//

#pragma once

#include "Device.h"
#include <cstddef>

namespace vgfx {

    class Device;

    class Context {
    public:
        virtual ~Context();

        /**
         * Return the associated device.
         * @return
         */
        Device* device() const {
            return _device;
        }

        /**
         * Return the number if bytes consumed by internal gpu cache.
         * @return
         */
        size_t memoryUsage() const;

        bool wait();


    protected:
        explicit Context(Device *device);

    private:
        Device *_device = nullptr;

        void releaseAll(bool releaseGPU);

        friend class Device;
    };

} // vgfx