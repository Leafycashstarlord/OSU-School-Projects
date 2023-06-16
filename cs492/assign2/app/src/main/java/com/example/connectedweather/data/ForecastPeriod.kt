package com.example.connectedweather.data

import com.squareup.moshi.Json

data class ForecastPeriod(
    val dt_txt: String,
    val pop: Double,
    val main: ForecastInfo,
    val weather: List<ForecastDesc>,
    val clouds: ForecastClouds,
    val wind: ForecastWind
) : java.io.Serializable
