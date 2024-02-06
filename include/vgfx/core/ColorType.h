//
// Created by Anatta Feng on 2024/1/12.
//
#pragma once

namespace vgfx {
/**
 * Describes how pixel bits encode color.
 */
enum class ColorType {
  /**
   * uninitialized.
   */
  Unknown,
  /**
   * Each pixel is stored as a single translucency (alpha) channel. This is very useful for storing
   * masks efficiently, for instance. No color information is stored. With this configuration, each
   * pixel requires 1 byte of memory.
   */
  ALPHA_8,
  /**
   * Each pixel is stored on 4 bytes. Each channel (RGB and alpha for translucency) is stored with 8
   * bits of precision (256 possible values). The channel order is: red, green, blue, alpha.
   */
  RGBA_8888,
  /**
   * Each pixel is stored on 4 bytes. Each channel (RGB and alpha for translucency) is stored with 8
   * bits of precision (256 possible values). The channel order is: blue, green, red, alpha.
   */
  BGRA_8888,
  /**
   * Each pixel is stored on 2 bytes, and only the RGB channels are encoded: red is stored with 5
   * bits of precision (32 possible values), green is stored with 6 bits of precision (64 possible
   * values), and blue is stored with 5 bits of precision.
   */
  RGB_565,
  /**
   * Each pixel is stored as a single grayscale level. No color information is stored. With this
   * configuration, each pixel requires 1 byte of memory.
   */
  Gray_8,
  /**
   * Each pixel is stored on 8 bytes. Each channel (RGB and alpha for translucency) is stored as a
   * half-precision floating point value. This configuration is particularly suited for wide-gamut
   * and HDR content.
   */
  RGBA_F16,
  /**
   * Each pixel is stored on 4 bytes. Each RGB channel is stored with 10 bits of precision (1024
   * possible values). There is an additional alpha channel that is stored with 2 bits of precision
   * (4 possible values). This configuration is suited for wide-gamut and HDR content which does not
   * require alpha blending, such that the memory cost is the same as RGBA_8888 while enabling
   * higher color precision.
   */
  RGBA_1010102
};
} // namespace vgfx