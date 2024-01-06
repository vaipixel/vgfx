//
// Created by 冯旭超 on 2024/1/7.
//

#include <android/log.h>
#include "utils/Logger.h"

#ifdef __ANDROID__
namespace vgfx {
#define LOG_TAG "vgfx"

    void logd(const std::string &message) {
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s", message.c_str());
    }
}
#endif