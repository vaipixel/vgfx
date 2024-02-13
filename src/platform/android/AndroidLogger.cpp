//
// Created by Anatta Feng on 2024/1/7.
//

#include <android/log.h>
#include "utils/Logger.h"
#include "vgfx/platform/Print.h"

#ifdef __ANDROID__
namespace vgfx {
#define LOG_TAG "vgfx"

void PrintLog(const char format[], ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, format, args);
  va_end(args);
}

void PrintWarn(const char format[], ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_WARN, LOG_TAG, format, args);
  va_end(args);
}

void PrintError(const char format[], ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, format, args);
  va_end(args);
}
}
#endif