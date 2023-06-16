package com.example.myapplication_final

class BookmarkedActivitiesRepository (private val activityDao: ActivityDao){
    suspend fun insertBookmarkedActivity(data: BoredData) = activityDao.insert(data)
    suspend fun deleteBookmarkedActivity(data: BoredData) = activityDao.delete(data)

    fun getBookmarkedActivities() = activityDao.getAllBookmarkedActivities()
}