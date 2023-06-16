package com.example.connectedweather.data

data class ForecastWind (
    val speed: Float,
    val deg: Int,
    val gust: Float
) : java.io.Serializable