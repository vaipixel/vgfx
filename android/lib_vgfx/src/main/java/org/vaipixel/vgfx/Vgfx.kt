package org.vaipixel.vgfx

class Vgfx {

    /**
     * A native method that is implemented by the 'vgfx' native library,
     * which is packaged with this application.
     */
    external fun draw();

    companion object {
        // Used to load the 'vgfx' library on application startup.
        init {
            System.loadLibrary("vgfx_jni")
        }
    }
}