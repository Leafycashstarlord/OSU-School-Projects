package com.example.roomyweather.data

class CityRepository(
    private val dao: CityDAO
) {
    suspend fun insertCity(city: RoomEntity) = dao.insert(city)
    suspend fun deleteCity(city: RoomEntity) = dao.delete(city)
    fun getAllCities() = dao.getAllCities()
}