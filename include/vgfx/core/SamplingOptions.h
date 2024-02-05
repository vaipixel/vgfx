//
// Created by Anatta Feng on 2024/2/6.
//

#pragma once

namespace vgfx {
    enum class FilterMode {
        Nearest,
        Linear,
    };

    enum class MipmapMode {
        None,
        Nearest,
        Linear,
    };

    struct SamplingOptions {
        SamplingOptions() = default;

        explicit SamplingOptions(FilterMode filterMode, MipmapMode mipmapMode = MipmapMode::None)
                : filterMode(filterMode), mipmapMode(mipmapMode) {

        }

        const FilterMode filterMode = FilterMode::Linear;

        const MipmapMode mipmapMode = MipmapMode::None;
    };
}