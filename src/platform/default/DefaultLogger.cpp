#include "utils/Logger.h"

//
// Created by 冯旭超 on 2024/1/7.
//
#if !defined(__ANDROID__)
namespace vgfx {
    void logd(const std::string &message) {
    }
}
#endif