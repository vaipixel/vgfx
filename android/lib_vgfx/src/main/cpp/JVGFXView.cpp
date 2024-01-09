//
// Created by Anatta Feng on 2024/1/10.
//

#include "JVGFXView.h"

static jfieldID VGFXView_nativePtr;

void JVGFXView::updateSize() {

}

void JVGFXView::draw() {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_vaipixel_vgfx_VGFXView_00024Companion_nativeInit(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeInit()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_vaipixel_vgfx_VGFXView_nativeRelease(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeRelease()
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_vaipixel_vgfx_VGFXView_00024Companion_setupFromSurface(JNIEnv *env, jobject thiz,
                                                                jobject surface, jfloat density) {
    // TODO: implement setupFromSurface()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_vaipixel_vgfx_VGFXView_updateSize(JNIEnv *env, jobject thiz) {
    // TODO: implement updateSize()
}