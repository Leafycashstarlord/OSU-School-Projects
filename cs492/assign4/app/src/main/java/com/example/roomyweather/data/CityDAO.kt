package com.example.roomyweather.data

import androidx.room.*
import kotlinx.coroutines.flow.Flow

@Dao
interface CityDAO {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(city: RoomEntity)

    @Delete
    suspend fun delete(city: RoomEntity)

    @Query("Select * FROM RoomEntity ORDER BY timestamp DESC")
    fun getAllCities(): Flow<List<RoomEntity>>
}