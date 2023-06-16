package com.example.connectedweather.data

import com.squareup.moshi.Json

data class ForecastDesc (
    @Json (name="main") val quickDesc: String,
    val description: String
) : java.io.Serializable