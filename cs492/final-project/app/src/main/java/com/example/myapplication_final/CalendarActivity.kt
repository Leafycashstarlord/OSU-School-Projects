package com.example.myapplication_final

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import android.app.SearchManager
import android.content.ActivityNotFoundException
import android.content.Intent
import android.util.Log
import android.widget.Button
import android.widget.TextView
import com.google.android.material.snackbar.Snackbar
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class CalendarActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.calendar)

        val backButton = findViewById<Button>(R.id.backButton)
        backButton.setOnClickListener {
            goBack()
        }
    }

    private fun goBack() {
        val intent = Intent(this, MainActivity::class.java)
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP)
        startActivity(intent)
    }
}
