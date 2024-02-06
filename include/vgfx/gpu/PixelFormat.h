//
// Created by Anatta Feng on 2024/1/17.
//

#pragma once

namespace vgfx {
/**
 * Describes the possible pixel formats of a TextureSampler.
 */
enum class PixelFormat {
  /**
   * uninitialized.
   */
  Unknown,
  /**
   * Pixel with 8 bits for alpha. Each pixel is stored on 1 byte.
   */
  ALPHA_8,
  /**
   * Pixel with 8 bits for grayscale. Each pixel is stored on 1 byte.
   */
  GRAY_8,
  /**
   * Pixel with 8 bits for red, green. Each pixel is stored on 2 bytes.
   */
  RG_88,
  /**
   * Pixel with 8 bits for red, green, blue, alpha. Each pixel is stored on 4 bytes.
   */
  RGBA_8888,
  /**
   * Pixel with 8 bits for blue, green, red, alpha. Each pixel is stored on 4 bytes.
   */
  BGRA_8888
};
}