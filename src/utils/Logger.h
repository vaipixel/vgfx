//
// Created by 冯旭超 on 2024/1/7.
//

#include <string>

namespace vgfx {

    void logd(const std::string &message);

#if DEBUG
#define DEBUG_ASSERT(assertion) ASSERT(assertion)
#else
#define DEBUG_ASSERT(assertion)
#endif

}