package org.vaipixel.vgfx.demo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import org.vaipixel.vgfx.Vgfx
import com.vaipixel.vgfx.demo.R

class MainActivity : AppCompatActivity() {
    private val vgfx = Vgfx()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        vgfx.draw()
    }
}