//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include "vgfx/gpu/Context.h"

namespace vgfx {

class GLInterface {
 public:
  static const GLInterface *Get(const Context *context);

 private:
  static const GLInterface *GetNative();

  static std::unique_ptr<const GLInterface> MakeNativeInterface();
};

} // vgfx