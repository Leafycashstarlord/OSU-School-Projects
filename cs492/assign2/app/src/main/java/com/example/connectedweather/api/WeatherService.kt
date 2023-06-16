package com.example.connectedweather.api

import com.example.connectedweather.data.ForecastPeriod
import retrofit2.Call
import retrofit2.Retrofit
import retrofit2.converter.moshi.MoshiConverterFactory
import retrofit2.http.GET
import retrofit2.http.Query

interface WeatherService {
    @GET("data/2.5/forecast")
    fun searchAPI(
        @Query("q") q: String,
        @Query("appid") appid: String = "5d181e7ecbf80f51a8c06f1b5929911b"
    ): Call<ForecastPeriod>

    companion object{
        private const val BASE_URL = "https://api.openweathermap.org/"

        fun create() : WeatherService {
            return Retrofit.Builder()
                .baseUrl(BASE_URL)
                .addConverterFactory(MoshiConverterFactory.create())
                .build()
                .create(WeatherService::class.java)
        }
    }
}