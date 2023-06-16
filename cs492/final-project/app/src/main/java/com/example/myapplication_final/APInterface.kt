package com.example.myapplication_final

import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Query

interface APInterface {
    @GET("activity")
    fun getData(
        @Query("type") type: String = "education"
    ): Call<BoredData>
}