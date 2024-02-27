//
// Created by Anatta Feng on 2024/2/27.
//

#pragma once

#include <memory>
#include "vgfx/core/Point.h"
#include "Texture.h"
#include "ProgramInfo.h"
namespace vgfx {

struct DstTextureInfo {
  bool requiresBarrier = false;
  Point offset = Point::Zero();
  std::shared_ptr<Texture> texture = nullptr;
};

/**
 * Pipeline is a ProgramInfo that uses a list of Processors to assemble a shader program and set API
 * state for a draw.
 */
class Pipeline : public ProgramInfo {

};

} // vgfx