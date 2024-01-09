//
// Created by Anatta Feng on 2024/1/7.
//
#pragma once

#include <memory>
#include "vgfx/gpu/Device.h"

namespace vgfx {

    class GLDevice : public Device {
    public:
        /**
         * Return the native handle of current OpenGL context on the calling thread.
         * @return
         */
        static void *CurrentNativeHandle();

        /**
         * Return an GLDevice associated with OpenGL context. Returns nullptr if there is no
         * current OpenGL context on the calling thread.
         * @return
         */
        static std::shared_ptr<GLDevice> Current();

        /**
         * Create a new GLDevice. If the creation fails, it will return a pre-created GLDevice. If that
         * also fails, it will return the active GLDevice of the current thread. If all attempts fail,
         * nullptr will be returned.
         * @return
         */
        static std::shared_ptr<GLDevice> MakeWithFallback();

        /**
         * Returns the GLDevice associated with the specified OpenGL context.
         * @param nativeHandle
         * @return
         */
        static std::shared_ptr<GLDevice> Get(void *nativeHandle);

        ~GLDevice() override;

        /**
         * Returns true if the specified native handle is shared context to this GLDevice.
         * @param nativeHandle
         * @return
         */
        virtual bool sharableWith(void *nativeHandle) const = 0;

    protected:
        void *nativeHandle = nullptr;
        bool externallyOwned = false;

        explicit GLDevice(void *nativeHandle);

        bool onLockContext() override;

        void onUnlockContext() override;

        virtual bool onMakeCurrent() = 0;

        virtual void onClearCurrent() = 0;
    };

} // vgfx
