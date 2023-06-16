package com.example.roomyweather.data

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [RoomEntity::class], version = 1, exportSchema = false)
abstract class CityDatabase: RoomDatabase() {
    abstract fun cityDao(): CityDAO

    companion object{
        @Volatile private var instance: CityDatabase? = null

        private fun buildDatabase(context: Context) =
            Room.databaseBuilder(
                context,
                CityDatabase::class.java,
                "searchedCity.db"
            ).build()

        fun getInstance(context: Context): CityDatabase{
            return instance ?: synchronized(this){
                instance ?: buildDatabase(context).also{
                    instance = it
                }
            }
        }
    }
}