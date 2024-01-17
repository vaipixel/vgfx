//
// Created by Anatta Feng on 2024/1/12.
//
#pragma once
namespace vgfx {
    /**
     * Textures and Surfaces can be stored such that (0, 0) in texture space may correspond to either the top-left or bottom-left content pixel.
     */
    enum class ImageOrigin {
        TopLeft,
        BottomLeft
    };
}