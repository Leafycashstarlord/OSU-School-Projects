package com.example.myapplication_final

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class BoredData(
    @PrimaryKey
    val activity: String,
    val type: String,
    val participants: Int,
    val price: Float,
    val link: String,
    val key: String,
    val accessibility: Float,
    var num: Int = 1
)