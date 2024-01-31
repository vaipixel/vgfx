//
// Created by Anatta Feng on 2024/1/7.
//

#include <string>
#include "vgfx/platform/Print.h"

namespace vgfx {

#define LOGI(...) ::vgfx::PrintLog(__VA_ARGS__)
#define LOGE(...) ::vgfx::PrintError(__VA_ARGS__)

#if DEBUG
#define DEBUG_ASSERT(assertion) ASSERT(assertion)
#else
#define DEBUG_ASSERT(assertion)
#endif

}