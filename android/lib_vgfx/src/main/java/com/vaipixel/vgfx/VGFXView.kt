package com.vaipixel.vgfx

import android.graphics.SurfaceTexture
import android.view.Surface
import android.view.TextureView

class VGFXView : TextureView, TextureView.SurfaceTextureListener {

    private var nativePtr: Long = 0

    private var surface: Surface? = null

    constructor(context: android.content.Context) : super(context) {
        setupSurfaceTexture()
    }

    constructor(context: android.content.Context, attrs: android.util.AttributeSet) : super(
        context,
        attrs
    ) {
        setupSurfaceTexture()
    }

    constructor(
        context: android.content.Context,
        attrs: android.util.AttributeSet,
        defStyleAttr: Int
    ) : super(context, attrs, defStyleAttr) {
        setupSurfaceTexture()
    }

    private fun setupSurfaceTexture() {
        surfaceTextureListener = this
    }

    override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
        release()
    }

    override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {
        TODO("Not yet implemented")
    }

    override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
        TODO("Not yet implemented")
    }

    override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {
        TODO("Not yet implemented")
    }

    private fun release() {

    }

    private external fun updateSize()

    private external fun nativeRelease()

    companion object {
        private external fun nativeInit()

        private external fun setupFromSurface(surface: Surface, density: Float): Long

        init {
            System.loadLibrary("vgfx_jni")
            nativeInit()
        }

    }
}