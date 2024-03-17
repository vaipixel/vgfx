//
// Created by Anatta Feng on 2024/3/16.
//

#pragma once

#include "vgfx/core/Data.h"

namespace vgfx {
/**
 * DataProvider defers the data generation until it is needed.
 */
class DataProvider {
 public:
  virtual ~DataProvider() = default;

  virtual std::shared_ptr<Data> getData() const = 0;
};

} // vgfx