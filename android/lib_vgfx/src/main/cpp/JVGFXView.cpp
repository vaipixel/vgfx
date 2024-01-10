//
// Created by Anatta Feng on 2024/1/10.
//

#include "JVGFXView.h"
#include "vgfx/opengl/egl/EGLWindow.h"

static jfieldID VGFXView_nativePtr;

void JVGFXView::updateSize() {

}

void JVGFXView::draw() {
    auto device = window->getDevice();
    auto context = device->lockContext();
    if (context == nullptr) {
        return;
    }
    auto surface = window->getSurface(context);
    if (surface == nullptr) {
        device->unlock();
        return;
    }
    auto canvas = surface->getCanvas()
}

static JVGFXView *GetJVGFXView(JNIEnv *env, jobject thiz) {
    return reinterpret_cast<JVGFXView *>(env->GetLongField(thiz, VGFXView_nativePtr));
}

extern "C"
JNIEXPORT void JNICALL
Java_org_vaipixel_vgfx_VGFXView_00024Companion_nativeInit(JNIEnv *env, jobject thiz) {
    auto clazz = env->FindClass("org/vaipixel/vgfx/VGFXView");
    VGFXView_nativePtr = env->GetFieldID(clazz, "nativePtr", "J");
}

extern "C"
JNIEXPORT void JNICALL
Java_org_vaipixel_vgfx_VGFXView_nativeRelease(JNIEnv *env, jobject thiz) {
    auto jVGFXView = GetJVGFXView(env, thiz);
    delete jVGFXView;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_vaipixel_vgfx_VGFXView_00024Companion_setupFromSurface(JNIEnv *env, jobject thiz,
                                                                jobject surface, jfloat density) {
    auto nativeWindow = ANativeWindow_fromSurface(env, surface);
    auto window = vgfx::EGLWindow::MakeFrom(nativeWindow);
    if (window == nullptr) {
        return 0;
    }
    return reinterpret_cast<jlong>(
            new JVGFXView(nativeWindow, std::move(window)));
}

extern "C"
JNIEXPORT void JNICALL
Java_org_vaipixel_vgfx_VGFXView_updateSize(JNIEnv *env, jobject thiz) {
    auto view = GetJVGFXView(env, thiz);
    if (view == nullptr) {
        return;
    }
    view->updateSize();
}
extern "C"
JNIEXPORT void JNICALL
Java_org_vaipixel_vgfx_VGFXView_nativeDraw(JNIEnv *env, jobject thiz) {
    auto view = GetJVGFXView(env, thiz);
    if (view == nullptr) {
        return;
    }
    view->draw();
}