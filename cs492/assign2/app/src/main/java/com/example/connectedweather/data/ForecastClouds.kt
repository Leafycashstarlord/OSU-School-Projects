package com.example.connectedweather.data

import com.squareup.moshi.Json

data class ForecastClouds (
    @Json (name = "all") val cloudPercent: Int
) : java.io.Serializable