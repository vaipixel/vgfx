//
// Created by Anatta Feng on 2024/3/16.
//

#pragma once

#include "vgfx/core/ImageGenerator.h"

namespace vgfx {
/**
 * ImageDecoder is a task that decodes an encoded image to an ImageBuffer.
 */
class ImageDecoder {
 public:
  /*
   * Create an ImageDecoder wraps a decoded ImageBuffer.
   */
  static std::shared_ptr<ImageDecoder> Wrap(std::shared_ptr<ImageBuffer> imageBuffer);

  /**
   * Create an ImageDecoder from the specified ImageGenerator. If asyncDecoding is true, the
   * returned ImageDecoder schedules an asynchronous image-decoding task immediately. Otherwise, the
   * image will be decoded synchronously when the decode() method is called.
   */
  static std::shared_ptr<ImageDecoder> MakeFrom(std::shared_ptr<ImageGenerator> generator,
                                                bool tryHardware = true, bool asyncDecoding = true);

  virtual ~ImageDecoder() = default;

  /**
   * Returns the width of the decoded image.
   */
  virtual int width() const = 0;

  /**
   * Returns the height of the decoded image.
   */
  virtual int height() const = 0;

  /**
   * Returns true if the decoded image represents transparency only.
   */
  virtual bool isAlphaOnly() const = 0;

  /**
   * Returns the decoded ImageBuffer.
   */
  virtual std::shared_ptr<ImageBuffer> decode() const = 0;

};

} // vgfx