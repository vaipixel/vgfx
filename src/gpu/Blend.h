//
// Created by Anatta Feng on 2024/2/27.
//

#pragma once

#include "vgfx/core/BlendMode.h"
namespace vgfx {

enum class BlendModeCoeff {
  /**
   * 0
   */
  Zero,
  /**
   * 1
   */
  One,
  /**
   * src color
   */
  SrcColor,
  /**
   * inverse src color (i.e. 1 - sc)
   */
  InverseSrcColor,
  /**
   * dst color
   */
  DstColor,
  /**
   * inverse dst color (i.e. 1 - dc)
   */
  InverseDstColor,
  /**
   * src alpha
   */
  SrcAlpha,
  /**
   * inverse src alpha (i.e. 1 - sa)
   */
  InverseSrcAlpha,
  /**
   * dst alpha
   */
  DstAlpha,
  /**
   * inverse dst alpha (i.e. 1 - da)
   */
  InverseDstAlpha,
};

struct BlendInfo {
  BlendModeCoeff srcBlend;
  BlendModeCoeff dstBlend;
};

/**
 * Returns true if 'mode' is a coefficient-based blend mode. If true is returned, the mode's src and
 * dst coefficient functions are set in 'src' and 'dst'.
 */
bool BlendModeAsCoeff(BlendMode mode, BlendInfo *blendInfo = nullptr);
} // vgfx