//
// Created by Anatta Feng on 2024/1/13.
//

#pragma once

#include "vgfx/opengl/GLTypes.h"
#include "vgfx/metal/MtlTypes.h"

namespace vgfx {
/**
 * Possible GPU backend APIs that may be used by VGFX.
 */
enum class Backend {
  /**
   * Mock is a backend that does not draw anything. It is used for unit tests and measure CPU
   * overhead.
   */
  MOCK,
  OPENGL,
  METAL,
  VULKAN
};

/**
 * Wrapper class for passing into and receiving data from VGFX about a backend texture object.
 */
class BackendTexture {
 public:
  /**
   * Creates an invalid backend render target.
   */
  BackendTexture() : _width(0), _height(0) {
  }

 private:
  Backend _backend = Backend::MOCK;
  int _width = 0;
  int _height = 0;

  union {
    GLTextureInfo glInfo;
    MtlTextureInfo mtlInfo;
  };
};

/**
 * Wrapper class for passing into and receiving data from VGFX about a backend render target object.
 */
class BackendRenderTarget {
 public:
  /**
   * Creates an invalid backend render target.
   */
  BackendRenderTarget() : _width(0), _height(0) {
  }

  /**
    * Creates an OpenGL backend render target.
    * @param glInfo
    * @param width
    * @param height
    * @return
    */
  BackendRenderTarget(const GLFrameBufferInfo &glInfo, int width, int height);

  /**
   * Create an Metal backend render target.
   * @param mtlInfo
   * @param width
   * @param height
   */
  BackendRenderTarget(const MtlTextureInfo &mtlInfo, int width, int height);

  BackendRenderTarget(const BackendRenderTarget &that);

  BackendRenderTarget &operator=(const BackendRenderTarget &);

  /**
   * Returns true if the backend texture has been initialized.
   * @return
   */
  bool isValid() const {
    return _width > 0 && _height > 0;
  }

  /**
   * Returns the width of this render target.
   * @return
   */
  int width() const {
    return _width;
  }

  /**
   * Returns the height of this render target.
   * @return
   */
  int height() const {
    return _height;
  }

  /**
   * Returns the backend API of this render target.
   * @return
   */
  Backend backend() const {
    return _backend;
  }

  /**
   * If the backend API is GL, copies a snapshot of the GLFramebufferInfo struct into the passed
   * in pointer and returns true. Otherwise, returns false if the backend API is not GL.
   * @param glFrameBufferInfo
   * @return
   */
  bool getGLFramebufferInfo(GLFrameBufferInfo *glFrameBufferInfo) const;

  /**
   * If the backend API is Metal, copies a snapshot of the MtlTextureInfo struct into the passed
   * in pointer and returns true. Otherwise, return false if the backend API is not Metal.
   * @param mtlTextureInfo
   * @return
   */
  bool getMtlTextureInfo(MtlTextureInfo *mtlTextureInfo) const;
 private:
  Backend _backend = Backend::MOCK;
  int _width = 0;
  int _height = 0;
  union {
    GLFrameBufferInfo glInfo;
    MtlTextureInfo mtlInfo;
  };
};

/**
 * Wrapper class for passing into and receiving data from VGFX about a backend semaphore object.
 */
class BackendSemaphore {
 public:
  BackendSemaphore();
  bool isInitialized() const {
    return _isInitialized;
  }

  void initGL(void *sync);

  void *glSync() const;

 private:
  Backend _backend = Backend::MOCK;
  union {
    void *_glSync;
  };
  bool _isInitialized;
};
} // vgfx