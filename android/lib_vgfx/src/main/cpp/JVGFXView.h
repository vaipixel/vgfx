//
// Created by Anatta Feng on 2024/1/10.
//

#pragma once

#include <android/native_window_jni.h>
#include <jni.h>
#include <string>
#include "vgfx/gpu/Window.h"

class JVGFXView {

public:
    explicit JVGFXView(ANativeWindow *nativeWindow, std::shared_ptr<vgfx::Window> window)
            : nativeWindow(nativeWindow), window(std::move(window)) {
        updateSize();
    }

    ~JVGFXView() {
        ANativeWindow_release(nativeWindow);
    }

    void updateSize();

    void draw();

private:
    ANativeWindow *nativeWindow = nullptr;
    std::shared_ptr<vgfx::Window> window;

};

