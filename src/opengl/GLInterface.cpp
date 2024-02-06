//
// Created by Anatta Feng on 2024/1/7.
//

#include <unordered_map>
#include "GLInterface.h"

namespace vgfx {
static std::mutex interfaceLocker = {};
static std::unordered_map<int, std::unique_ptr<const GLInterface>> glInterfaceMap = {};

static int GetGLVersion() {
  return 0;
}
} // vgfx