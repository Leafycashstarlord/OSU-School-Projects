package com.example.myapplication_final

import androidx.room.*
import kotlinx.coroutines.flow.Flow

@Dao
interface ActivityDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(data: BoredData)

    @Delete
    suspend fun delete(data: BoredData)

    @Query("SELECT * FROM BoredData")
    fun getAllBookmarkedActivities(): Flow<List<BoredData>>
}