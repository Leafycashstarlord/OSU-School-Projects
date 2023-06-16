package com.example.roomyweather.data

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class RoomEntity(
    @PrimaryKey
    val location: String,
    val timestamp: Long
)