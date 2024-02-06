//
// Created by Anatta Feng on 2024/1/15.
//

#pragma once

#include <memory>
#include "TextureProxy.h"
#include "gpu/RenderTarget.h"
#include "ResourceProxy.h"
#include "vgfx/platform/HardwareBuffer.h"
#include "vgfx/gpu/PixelFormat.h"
#include "gpu/Texture.h"

namespace vgfx {

/**
 * This class delays the acquisition of render targets until they are actually required.
 */
class RenderTargetProxy : public ResourceProxy {

 public:
  /**
   * Creates a new RenderTargetProxy with an exising backend render target.
   * @param context
   * @param backendRenderTarget
   * @param origin
   * @return
   */
  static std::shared_ptr<RenderTargetProxy> MakeFrom(Context *context,
                                                     const BackendRenderTarget &backendRenderTarget,
                                                     ImageOrigin origin = ImageOrigin::TopLeft);

  /**
   * Creates a new RenderTargetProxy with an existing backend render texture. If adapted is true, the
   * backend texture will be destroyed at a later point after the proxy is released.
   * @param context
   * @param backendTexture
   * @param sampleCount
   * @param origin
   * @param adopted
   * @return
   */
  static std::shared_ptr<RenderTargetProxy> MakeFrom(Context *context,
                                                     const BackendTexture &backendTexture,
                                                     int sampleCount = 1,
                                                     ImageOrigin origin = ImageOrigin::TopLeft,
                                                     bool adopted = false);

  /**
   * Creates a new RenderTargetProxy with an existing HardwareBuffer.
   * @param context
   * @param hardwareBuffer
   * @param sampleCount
   * @return
   */
  static std::shared_ptr<RenderTargetProxy> MakeFrom(Context *context,
                                                     HardwareBufferRef hardwareBuffer,
                                                     int sampleCount = 1);

  /**
   * Creates a new RenderTargetProxy instance with specified context, width, height, format, sample
   * count, mipmap state and origin.
   * @param width
   * @param height
   * @param format
   * @param sampleCount
   * @param mipMapped
   * @param origin
   * @return
   */
  static std::shared_ptr<RenderTargetProxy> Make(Context *const, int width, int height,
                                                 PixelFormat format, int sampleCount = 1,
                                                 bool mipMapped = false,
                                                 ImageOrigin origin = ImageOrigin::TopLeft);

  /**
   * Returns the width of the render target.
   * @return
   */
  int width() const {
    return _width;
  }

  /**
   * Returns the height of the render target.
   * @return
   */
  int height() const {
    return _height;
  }

  /**
   * Returns the pixel format of the render target.
   * @return
   */
  PixelFormat format() const {
    return _format;
  }

  /**
   * If we are instantiated and have a render target, return the sampleCount value of that render
   * target. Otherwise, returns the proxy's sampleCount value from creation time.
   * @return
   */
  int sampleCount() const {
    return _sampleCount;
  }

  /**
   * Returns the origin of the render target, either ImageOrigin::TopLeft or
   * ImageOrigin::BottomLeft.
   * @return
   */
  ImageOrigin origin() const {
    return _origin;
  }

  /**
   * Returns the associated TextureProxy instance. Returns nullptr if the RenderTargetProxy if not
   * backed by a texture.
   * @return
   */
  virtual std::shared_ptr<TextureProxy> getTextureProxy() const {
    return nullptr;
  }

  /**
   * Returns true if the proxy was backed by a texture.
   * @return
   */
  bool isTextureBackend() const;

  /**
   * Returns the backing Texture of the proxy. Returns nullptr if the proxy is not instantiated yet,
   * or it is not backed by a texture.
   * @return
   */
  std::shared_ptr<Texture> getTexture() const;

  /**
   * Creates a compatible TextureProxy instance matches the properties of the RenderTargetProxy.
   * @return
   */
  std::shared_ptr<RenderTarget> getRenderTarget() const;

  /**
   * Ceates a compatible TextureProxy instance matches the properties of the RenderTargetProxy.
   * @return
   */
  std::shared_ptr<TextureProxy> makeTextureProxy() const;

  /**
   * Creates a compatible RenderTargetProxy instance matches the properties of this one.
   * @return
   */
  std::shared_ptr<RenderTargetProxy> makeRenderTargetProxy() const;

 protected:
  RenderTargetProxy(int width, int height, PixelFormat format, int sampleCount, ImageOrigin origin);

 private:
  int _width = 0;
  int _height = 0;
  PixelFormat _format = PixelFormat::RGBA_8888;
  int _sampleCount = 1;
  ImageOrigin _origin = ImageOrigin::TopLeft;

  friend class ProxyProvider;
};

} // vgfx