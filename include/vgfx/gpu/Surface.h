//
// Created by Anatta Feng on 2024/1/7.
//
#pragma once

#include "vgfx/core/Canvas.h"
#include "vgfx/gpu/SurfaceOptions.h"
#include "vgfx/core/ColorType.h"
#include "vgfx/core/Image.h"
#include "gpu/proxies/TextureProxy.h"
#include "gpu/Backend.h"
#include "vgfx/platform/HardwareBuffer.h"

namespace vgfx {
    class Canvas;

    class Context;

    class RenderTarget;

    class RenderTargetProxy;

    /**
     * The Surface class is responsible for managing the pixels that a Canvas draws into. The Surface
     * takes care of allocating a Canvas that will draw into the surface. Call surface->getCanvas() to
     * use that Canvas (but don't delete it, it is owned by the surface). The Surface always has
     * non-zero dimensions. If there is a request for a new surface, and either of the requested
     * dimensions is zero, then nullptr will be returned.
     */
    class Surface {
    public:
        /**
         * Create a new Surface on GPU indicated by context. Allocates memory for pixels based on the
         * width, height, and color type (alpha only). A Surface with MSAA enabled is returned if the
         * sample count is greater than 1. Return nullptr if the size is invalid or the alpha-only
         * textures are not renderable in the GPU backend.
         * @param context
         * @param width
         * @param height
         * @param alphaOnly
         * @param sampleCount
         * @param mipMapped
         * @param options
         * @return
         */
        static std::shared_ptr<Surface> Make(Context *context, int width, int height,
                                             bool alphaOnly = false, int sampleCount = 1,
                                             bool mipMapped = false,
                                             const SurfaceOptions *options = nullptr);

        /**
         * Creates a new Surface on GPU indicated by context. Allocates memory for pixels based on the
         * width, height, and colorType. A Surface with MSAA enabled is returned if the sample count is
         * greater than 1. Return nullptr if the size is invalid or the colorType is not renderable in
         * the GPU backend.
         * @param context
         * @param width
         * @param height
         * @param colorType
         * @param sampleCount
         * @param mipMapped
         * @param options
         * @return
         */
        static std::shared_ptr<Surface> Make(Context *context, int width, int height, ColorType colorType,
                                             int sampleCount = 1, bool mipMapped = false,
                                             const SurfaceOptions *options = nullptr);

        /**
         * Wraps a backend render target into Surface. The caller must ensure the renderTarget is valid
         * for the lifetime of the returned Surface. Returns nullptr if the context is nullptr or the
         * renderTarget is invalid.
         * @param context
         * @param renderTarget
         * @param origin
         * @param options
         * @return
         */
        static std::shared_ptr<Surface> MakeFrom(Context *context,
                                                 const BackendRenderTarget &renderTarget,
                                                 ImageOrigin origin,
                                                 const SurfaceOptions *options = nullptr);

        /**
         * Wraps a BackendTexture into the Surface. The caller must ensure the texture is valid for the
         * lifetime of the returned Surface. If the sampleCount is greater than zero, creates an
         * intermediate MSAA Surface which is used for drawing backendTexture. Return nullptr if the
         * context is nullptr or the texture is not renderable in the GPU backend.
         * @param context
         * @param backendTexture
         * @param origin
         * @param sampleCount
         * @param options
         * @return
         */
        static std::shared_ptr<Surface> MakeFrom(Context *context, const BackendTexture &backendTexture,
                                                 ImageOrigin origin, int sampleCount = 1,
                                                 const SurfaceOptions *options = nullptr);

        /**
         * Creates a Surface from the platform-specific hardware buffer. For example, the hardware buffer
         * could be an AHardwareBuffer on the android platform or a CVPixelBufferRef on the apple
         * platform. The returned Surface takes a reference to the hardwareBuffer. Returns nullptr if the
         * context is nullptr or the hardwareBuffer is not renderable.
         * @param context
         * @param hardwareBuffer
         * @param sampleCount
         * @param options
         * @return
         */
        static std::shared_ptr<Surface> MakeFrom(Context *context, HardwareBufferRef hardwareBuffer,
                                                 int sampleCount = 1,
                                                 const SurfaceOptions *options = nullptr);

        virtual ~Surface();

        /**
         * Retrieves the context associated with this Surface.
         * @return
         */
        Context *getContext() const;

        /**
         * Returns the SurfaceOptions of the Surface.
         * @return
         */
        const SurfaceOptions *options() const {
            return &surfaceOptions;
        }

        /**
         * Returns the width of this surface.
         * @return
         */
        int width() const;

        /**
         * Returns the height of this surface.
         * @return
         */
        int height() const;

        /**
         * Returns the origin of this surface, either SurfaceOrigin::TopLeft or SurfaceOrigin::BottomLeft.
         * @return
         */
        ImageOrigin origin() const;

        /**
         * Retrieves the backend render target that the surface renders to. The returned
         * BackendRenderTarget should be discarded if the Surface is drawn to or deleted.
         * @return
         */
        BackendRenderTarget getBackendRenderTarget();

        /**
         * Retrieves the backend texture that the surface renders to. Returns an invalid BackendTexture if
         * the surface has no backend texture. The returned BackendTexture should be discarded if the
         * Surface is drawn to or deleted.
         * @return
         */
        BackendTexture getBackendTexture();

        /**
         * Retrieves the backing hardware buffer. This method does not acquire any additional reference to
         * the returned hardware buffer. Returns nullptr if the surface is not created from a hardware
         * buffer.
         * @return
         */
        HardwareBufferRef gethardwareBuffer();

        /**
         * Returns Canvas that draws into the Surface. Subsequent calls return the same Canvas. Canvas
         * returned is managed and owned by Surface, and is deleted when the Surface is deleted.
         * @return
         */
        Canvas *getCanvas();

        /**
         * Inserts a GPU semaphore that the current GPU-backend API must wait on before executing any more
         * commands on the GPU for this surface. Surface will take ownership of the underlying semaphore
         * and delete it once it has been signaled and waited on. If this call returns false, then the
         * GPU backend will not wait on the passed semaphore, and the client will still own the
         * semaphore. Returns true if GPU is waiting on the semaphore.
         * @param waitSemaphore
         * @return
         */
        bool wait(const BackendSemaphore &waitSemaphore);

    private:
        std::shared_ptr<RenderTargetProxy> renderTargetProxy = nullptr;
        SurfaceOptions surfaceOptions = {};
        Canvas *canvas = nullptr;
        std::shared_ptr<Image> cacheImage = nullptr;

        static std::shared_ptr<Surface> MakeFrom(std::shared_ptr<RenderTargetProxy> renderTargetProxy,
                                                 const SurfaceOptions *options = nullptr);

        Surface(std::shared_ptr<RenderTargetProxy> proxy, const SurfaceOptions *options);

        std::shared_ptr<TextureProxy> getTextureProxy();

        void aboutToDraw(bool discardContent = false);
    };

}

