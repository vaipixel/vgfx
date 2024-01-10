//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "vgfx/gpu/Surface.h"

namespace vgfx {
    /**
     * Window represents a native displayable resource that can be rendered or written to by a Device.
     */
    class Window {
    public:
        virtual ~Window() = default;

        /**
         * Returns the Device associated with this Window. It may return null if the window is still in
         * the process of initializing.
         * @return
         */
        std::shared_ptr<Device> getDevice();

        /**
         * Returns the Surface associated with this Window. If the queryOnly is true, it will not create
         * a new surface if it doesn't exist.
         * @param context
         * @param queryOnly
         * @return
         */
        std::shared_ptr<vgfx::Surface> getSurface(Context *context, bool queryOnly = false);

        /**
         * Applies all pending graphics changes to the window. On the Android platform,
         * the presentationTime will be passed to the SurfaceTexture.getTimestamp() method,
         * while it will be ignored an other platforms. The time is measured in microseconds.
         * If the presentationTime is not set, a system timestamp will be used instead.
         * @param context
         * @param presentationTime
         */
        void present(Context *context, int64_t presentationTime = INT16_MIN);

        /**
         * Invalidates the cached surface associated with this Window. This is useful when the window is
         * resized and the surface needs to be recreated.
         */
        void invalidSize();

        /**
         * Free the cached surface associated with this Window immediately. This is useful when the
         * window is hidden and the surface is no longer needed for a while.
         */
        void freeSurface();

    protected:
        std::mutex locker = {};
        bool sizeInvalid = false;
        std::shared_ptr<Device> device = nullptr;
        std::shared_ptr<Surface> surface = nullptr;

        explicit Window(std::shared_ptr<Device> device);

        Window() = default;

        virtual std::shared_ptr<Surface> onCreateSurface(Context *context) = 0;

        virtual void onPresent(Context *context, int64_t presentationTime) = 0;

        virtual void onFreeSurface();

    private:
        bool checkContext(Context *context);
    };
}




