//
// Created by Anatta Feng on 2024/1/10.
//

#pragma once

#include <EGL/egl.h>
#include "EGLDevice.h"
#include "vgfx/gpu/Window.h"
#include "vgfx/gpu/Surface.h"

namespace vgfx {

class EGLWindow : public Window {
 public:
  /**
   * Returns an EGLWindow associated with current EGLSurface. Returns nullptr if there is no current
   * EGLSurface on the calling thread.
  */
  static std::shared_ptr<EGLWindow> Current();

  /**
   * Creates a new window from an EGL native window with specified shared context.
  */
  static std::shared_ptr<EGLWindow> MakeFrom(EGLNativeWindowType nativeWindow,
                                             EGLContext sharedContext = nullptr);

 protected:
  std::shared_ptr<Surface> onCreateSurface(Context *context) override;

  void onPresent(vgfx::Context *context, int64_t presentationTime) override;

 private:
  EGLNativeWindowType nativeWindow;

  explicit EGLWindow(std::shared_ptr<Device> device);

};

} // vgfx