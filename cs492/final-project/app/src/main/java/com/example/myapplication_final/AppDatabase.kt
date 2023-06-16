package com.example.myapplication_final

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [BoredData::class], version = 1)
abstract class AppDatabase: RoomDatabase() {
    abstract fun  dataDao(): ActivityDao

    companion object{
        @Volatile private var instance: AppDatabase? = null

        private fun buildDatabase(context: Context) =
            Room.databaseBuilder(
                context,
                AppDatabase::class.java,
                "bookmarkedActivities.db"
            ).build()

        fun getInstance(context: Context): AppDatabase{
            return instance ?: synchronized(this){
                instance ?: buildDatabase(context).also {
                    instance = it
                }
            }
        }
    }
}