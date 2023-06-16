package com.example.connectedweather.data

data class ForecastInfo (
    val temp_min: Double,
    val temp_max: Double,
    val humidity: Int
) : java.io.Serializable