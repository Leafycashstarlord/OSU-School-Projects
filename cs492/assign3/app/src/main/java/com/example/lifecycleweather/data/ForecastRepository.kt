package com.example.lifecycleweather.data

import com.example.lifecycleweather.api.OpenWeatherService
import com.example.lifecycleweather.ui.OPENWEATHER_APPID
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext

class ForecastRepository(private val service: OpenWeatherService,
                         private val dispatcher: CoroutineDispatcher = Dispatchers.IO) {
    suspend fun loadRepositoriesSearch(location: String?, units: String?): Result<FiveDayForecast> =
        withContext(dispatcher){
            try{
                val response = service.loadFiveDayForecast(location, units, OPENWEATHER_APPID)
                if(response.isSuccessful){
                    Result.success(response.body() !!)
                }else{
                    Result.failure(Exception(response.errorBody()?.string()))
                }
            }catch(e: Exception){
                Result.failure(e)
            }
        }
}