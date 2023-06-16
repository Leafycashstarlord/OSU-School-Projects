package com.example.basicweather

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.LinearLayoutManager
class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val weatherListRV: RecyclerView = findViewById(R.id.rv_weather_list)
        weatherListRV.layoutManager = LinearLayoutManager(this)
        weatherListRV.setHasFixedSize(true)

        val adapter = WeatherAdapter()
        weatherListRV.adapter = adapter

        adapter.addWeather(Weather("Jan 28", "49 F", "36 F", "55% precip.", "Sunny", "Clear skies, go surfing"))
        adapter.addWeather(Weather("Jan 27", "48 F", "35 F", "54% precip.", "Hurricane", "Cat 5 conditions, RUN!"))
        adapter.addWeather(Weather("Jan 26", "47 F", "34 F", "53% precip.", "AM Snow/PM Rain", "About 5 inches int he morning, light showers in the evening"))
        adapter.addWeather(Weather("Jan 25", "46 F", "33 F", "52% precip.", "Hurricane", "Cat 3 conditions, take shelter"))
        adapter.addWeather(Weather("Jan 24", "45 F", "32 F", "51% precip.", "Light Snow", "3 Inches in the morning"))
        adapter.addWeather(Weather("Jan 23", "44 F", "31 F", "50% precip.", "Blizzard", "Heavy snow all day, expect at least 10 inches"))
        adapter.addWeather(Weather("Jan 22", "45 F", "30 F", "30% precip.", "AM Showers", "Heavy Rain in the early morning"))
        adapter.addWeather(Weather("Jan 21", "45 F", "35 F", "50% precip.", "Showers", "Rain throughout the midmorning and afternoon"))
        adapter.addWeather(Weather("Jan 20", "48 F", "38 F", "30% precip.", "Mostly Cloudy", "Cloudy all day and night"))
        adapter.addWeather(Weather("Jan 19", "49 F", "36 F", "15% precip.", "Partly Cloudy", "Cloudy throughout the day and into the evening"))
        adapter.addWeather(Weather("Jan 18", "49 F", "33 F", "10% precip.", "Partly Cloudy", "Clouds in the morning to the afternoon"))
        adapter.addWeather(Weather("Jan 17", "53 F", "36 F", "60% precip.", "AM Showers", "Chance of light rain in the morning"))
        adapter.addWeather(Weather("Jan 16", "47 F", "39 F", "10% precip.", "AM fog/PM Clouds", "Minimal visability in the morning with cloudy skies at night"))
        adapter.addWeather(Weather("Jan 15", "55 F", "39 F", "80% precip.", "AM Showers", "Very high chance of rain in the morning"))
        adapter.addWeather(Weather("Jan 14", "51 F", "43 F", "25% precip.", "Mostly Sunny", "Mostly sunny with some increasing cloud coverage in the evening"))
    }
}