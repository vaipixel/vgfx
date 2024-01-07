//
// Created by 冯旭超 on 2024/1/7.
//

#pragma once

#include <mutex>
#include "Context.h"
#include <cstdint>

namespace vgfx {
    class Context;

    class Device {
    public:
        virtual ~Device();

        Context *lockContext();

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

