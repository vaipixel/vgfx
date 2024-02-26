//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

namespace vgfx {

/**
 * Defines constant values for visual blend mode effects.
 */
enum class BlendMode {
  /**
   * Replaces destination with zero: fully transparent.
   */
  Clear,
  /**
   * Replaces destination.
   */
  Src,
  /**
   * Preserves destination.
   */
  Dst,
  /**
   * Source over destination.
   */
  SrcOver,
  /**
   * Destination over source.
   */
  DstOver,
  /**
   * Source trimmed inside destination.
   */
  SrcIn,
  /**
   * Destination trimmed by source.
   */
  DstIn,
  /**
   * Source trimmed outside destination.
   */
  SrcOut,
  /**
   * Destination trimmed outside source.
   */
  DstOut,
  /**
   * Source inside destination blended with destination.
   */
  SrcATop,
  /**
   * Destination inside source blended with source.
   */
  DstATop,
  /**
   * Each of source and destination trimmed outside the other.
   */
  Xor,
  /**
   * Sum of colors.
   */
  Plus,
  /**
   * Product of premultiplied colors; darkens destination.
   */
  Modulate,
  /**
   * Multiply inverse of pixels, inverting result; brightens destination.
   */
  Screen,
  /**
   * Multiply or screen, depending on destination.
   */
  Overlay,
  /**
   * Darker of source and destination.
   */
  Darken,
  /**
   * Lighter of source and destination.
   */
  Lighten,
  /**
   * Brighten destination to reflect source.
   */
  ColorDodge,
  /**
   * Darken destination to reflect source.
   */
  ColorBurn,
  /**
   * Multiply or screen, depending on source.
   */
  HardLight,
  /**
   * Lighten or darken, depending on source.
   */
  SoftLight,
  /**
   * Subtract darker from lighter with higher contrast.
   */
  Difference,
  /**
   * Subtract darker from lighter with lower contrast.
   */
  Exclusion,
  /**
   * Multiply source with destination, darkening image.
   */
  Multiply,
  /**
   * Hue of source with saturation and luminosity of destination.
   */
  Hue,
  /**
   * Saturation of source with hue and luminosity of destination.
   */
  Saturation,
  /**
   * Hue and saturation of source with luminosity of destination.
   */
  Color,
  /**
   * Luminosity of source with hue and saturation of destination.
   */
  Luminosity
};
}