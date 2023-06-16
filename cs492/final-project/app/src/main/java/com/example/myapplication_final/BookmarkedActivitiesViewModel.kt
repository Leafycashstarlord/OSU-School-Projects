package com.example.myapplication_final

import android.app.Application
import androidx.lifecycle.*
import kotlinx.coroutines.launch


class BookmarkedActivitiesViewModel(application: Application): AndroidViewModel(application) {
    private val repository = BookmarkedActivitiesRepository(
        AppDatabase.getInstance(application).dataDao()
    )

    val bookmarkedActivities = repository.getBookmarkedActivities().asLiveData()

    fun addBookmarkedActivity(data: BoredData){
        viewModelScope.launch{
            repository.insertBookmarkedActivity(data)
        }
    }

    fun deleteBookmarkedActivity(data: BoredData){
        viewModelScope.launch{
            repository.deleteBookmarkedActivity(data)
        }
    }
}