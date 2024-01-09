#include "utils/Logger.h"

//
// Created by Anatta Feng on 2024/1/7.
//
#if !defined(__ANDROID__)
namespace vgfx {
    void logd(const std::string &message) {
    }
}
#endif