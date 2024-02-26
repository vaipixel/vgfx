//
// Created by Anatta Feng on 2024/2/6.
//

#pragma once

#include "gpu/processors/Processor.h"
#include "gpu/CoordTransform.h"
#include "gpu/SamplerState.h"
#include "vgfx/core/Image.h"
#include "gpu/DrawArgs.h"
#include "vgfx/core/TileMode.h"
#include "vgfx/core/Shader.h"

namespace vgfx {

class FragmentProcessor : public Processor {
 public:

  static std::unique_ptr<FragmentProcessor> Make(std::shared_ptr<Image> image, const DrawArgs &args,
                                                 const Matrix *localMatrix = nullptr,
                                                 TileMode tileModeX = TileMode::Clamp,
                                                 TileMode tileModeY = TileMode::Clamp);

  static std::unique_ptr<FragmentProcessor> Make(std::shared_ptr<Shader> shader,
                                                 const DrawArgs &args,
                                                 const Matrix *localMatrix = nullptr);

  static std::unique_ptr<FragmentProcessor> MulChildByInputAlpha(
      std::unique_ptr<FragmentProcessor> child);

  static std::unique_ptr<FragmentProcessor> MulInputByChildAlpha(
      std::unique_ptr<FragmentProcessor> child, bool inverted = false
  );

  static std::unique_ptr<FragmentProcessor> Compose(std::unique_ptr<FragmentProcessor> f,
                                                    std::unique_ptr<FragmentProcessor> g);

  size_t numTextureSamplers() const {
    return onCountTextureSamplers();
  }

  const TextureSampler* textureSampler(size_t i) const {
    return onTextureSampler(i);
  }

  void computeProcessorKey(Context *context, BytesKey *bytesKey) const override;

  size_t numChildProcessors() const {
    return childProcessors.size();
  }

  const FragmentProcessor* childProcessor(size_t index) const {
    return childProcessors[index].get();
  }

  size_t numCoordTransforms() const {
    return coordTransforms.size();
  }

  const CoordTransform* coordTransform(size_t index) const {
    return coordTransforms[index];
  }

  struct EmitArgs {
    EmitArgs(FragmentShaderBuilder* fragBuilder, UniformHandler* uniformHandler,
             std::string outputColor, std::string inputColor,
             const TransformedCoordVars* transformedCoords, const TextureSamplers* textureSamplers,
             std::function<std::string(std::string_view)> coordFunc = {})
        : fragBuilder(fragBuilder), uniformHandler(uniformHandler),
          outputColor(std::move(outputColor)), inputColor(std::move(inputColor)),
          transformedCoords(transformedCoords), textureSamplers(textureSamplers),
          coordFunc(std::move(coordFunc)) {
    }

    /**
     * Interface used to emit code in the shaders.
     */
    FragmentShaderBuilder* fragBuilder;
    UniformHandler* uniformHandler;
    /**
     * A predefined vec4 in the FS in which the stage should place its output color (or coverage).
     */
    const std::string outputColor;
    /**
     * A vec4 that holds the input color to the stage in the FS.
     */
    const std::string inputColor;
    /**
     * Fragment shader variables containing the coords computed using each of the
     * FragmentProcessor's CoordTransforms.
     */
    const TransformedCoordVars* transformedCoords;
    /**
     * Contains one entry for each TextureSampler of the Processor. These can be passed to the
     * builder to emit texture reads in the generated code.
     */
    const TextureSamplers* textureSamplers;
    const std::function<std::string(std::string_view)> coordFunc;
  };

 private:
  virtual void onComputeProcessorKey(BytesKey* bytesKey) const {

  }

  virtual size_t onCountTextureSamplers() const {
    return 0;
  }

  virtual const TextureSampler* onTextureSampler(size_t) const {
    return nullptr;
  }

  virtual SamplerState onSamplerState(size_t) const {
    return {};
  }

  virtual bool onIsEqual(const FragmentProcessor&) const {
    return true;
  }

  void internalEmitChild(size_t, const std::string &, const std::string &, EmitArgs &,
                         std::function<std::string(std::string_view)> = {}) const;
  std::vector<const CoordTransform*> coordTransforms;
  std::vector<std::unique_ptr<FragmentProcessor>> childProcessors;
};

} // vgfx