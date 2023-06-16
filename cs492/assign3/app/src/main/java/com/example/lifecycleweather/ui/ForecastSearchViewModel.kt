package com.example.lifecycleweather.ui

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.lifecycleweather.api.OpenWeatherService
import com.example.lifecycleweather.data.FiveDayForecast
import com.example.lifecycleweather.data.ForecastRepository
import com.example.lifecycleweather.data.LoadingStatus
import kotlinx.coroutines.launch

class ForecastSearchViewModel: ViewModel() {
    private val repository = ForecastRepository(OpenWeatherService.create())

    private val _searchResults = MutableLiveData<FiveDayForecast>(null)
    val searchResults: LiveData<FiveDayForecast> = _searchResults

    private val _errorMessage = MutableLiveData<String?>(null)
    val errorMessage: LiveData<String?> = _errorMessage

    private val _loadingStatus = MutableLiveData<LoadingStatus>(LoadingStatus.SUCCESS)
    val loadingStatus: LiveData<LoadingStatus> = _loadingStatus

    fun loadSearchResults(location: String?, units: String?){
        viewModelScope.launch {
            _loadingStatus.value = LoadingStatus.LOADING
            val result = repository.loadRepositoriesSearch(location, units)
            _searchResults.value = result.getOrNull()
            _errorMessage.value = result.exceptionOrNull()?.message
            _loadingStatus.value = when(result.isSuccess){
                true -> LoadingStatus.SUCCESS
                false -> LoadingStatus.ERROR
            }
        }
    }
}