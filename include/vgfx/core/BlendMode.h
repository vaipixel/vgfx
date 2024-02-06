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
  Src,
  Dst,
  /**
   * Source over destination.
   */
  SrcOver,

};
}