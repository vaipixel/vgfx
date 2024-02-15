//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <cstdint>
#include "vgfx/core/Rect.h"
#include "vgfx/core/Matrix.h"
#include "vgfx/gpu/Context.h"
namespace vgfx {

#define DEFINE_OP_CLASS_ID                    \
  static uint8_t ClassID() {                  \
    static uint8_t ClassID = GenOpClassID();  \
    return ClassID;                           \
  }

class Op {
 public:
  explicit Op(uint8_t classID) : _classID(classID) {

  }

  virtual ~Op() = default;

  virtual void prepare(Context *) {

  }
  virtual void execute(RenderPass *renderPass) = 0;

  bool combineIfPossible(Op *op);

  const Rect &bounds() const {
    return _bounds;
  }
 protected:
  static uint8_t GenOpClassID();

  void setBounds(Rect bounds) {
    _bounds = bounds;
  }

  void setTransformedBounds(const Rect &srcBounds, const Matrix &matrix) {
    _bounds = matrix.mapRect(srcBounds);
  }

  virtual bool onCombineIfPossible(Op *) {
    return false;
  }

 private:
  uint8_t _classID = 0;
  Rect _bounds = Rect::MakeEmpty();
};

} // vgfx