//
// Created by Anatta Feng on 2024/1/17.
//

#pragma once

#include <cstdio>
#include "vgfx/core/ColorType.h"
#include "vgfx/gpu/PixelFormat.h"

namespace vgfx {
PixelFormat ColorTypeToPixelFormat(ColorType type);

ColorType PixelFormatToColorType(PixelFormat format);

size_t PixelFormatBytesPerPixel(PixelFormat format);
} // vgfx