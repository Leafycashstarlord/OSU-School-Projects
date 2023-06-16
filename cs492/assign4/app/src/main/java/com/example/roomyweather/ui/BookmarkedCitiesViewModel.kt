package com.example.roomyweather.ui

import android.app.Application
import androidx.lifecycle.*
import androidx.room.Room
import com.example.roomyweather.data.CityDatabase
import com.example.roomyweather.data.CityRepository
import com.example.roomyweather.data.RoomEntity
import kotlinx.coroutines.launch

class BookmarkedCitiesViewModel(application: Application): AndroidViewModel(application) {
    private val cityRepo = CityRepository(
        CityDatabase.getInstance(application).cityDao()
    )

    val cities = cityRepo.getAllCities().asLiveData()

    fun addCity(city: RoomEntity){
        viewModelScope.launch {
            cityRepo.insertCity(city)
        }
    }

}