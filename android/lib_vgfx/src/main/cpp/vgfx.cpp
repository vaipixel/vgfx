#include <jni.h>
#include <string>
#include <vgfx/core/Canvas.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_vaipixel_vgfx_Vgfx_draw(JNIEnv *env, jobject thiz) {
    vgfx::Canvas canvas;
    canvas.draw();
}