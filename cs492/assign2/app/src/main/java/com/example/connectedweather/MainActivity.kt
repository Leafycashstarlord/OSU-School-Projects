package com.example.connectedweather

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.connectedweather.api.WeatherService
import com.google.android.material.progressindicator.CircularProgressIndicator
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import com.example.connectedweather.data.ForecastPeriod

class MainActivity : AppCompatActivity() {
    private val TAG = "MainActivity"
    private val location = "Corvallis,OR,US"

    private val weatherService = WeatherService.create()
    private val repoListAdapter = ForecastAdapter(::onForecastPeriodClick)

    private lateinit var searchResultsListRV: RecyclerView
    private lateinit var searchErrorTV: TextView
    private lateinit var loadingIndicator: CircularProgressIndicator

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        searchErrorTV = findViewById(R.id.tv_search_error)
        loadingIndicator = findViewById(R.id.loading_indicator)

        val forecastListRV = findViewById<RecyclerView>(R.id.rv_forecast_list)
        forecastListRV.layoutManager = LinearLayoutManager(this)
        forecastListRV.setHasFixedSize(true)
        val forecastDataItems = this.doRepoSearch()
        forecastListRV.adapter = repoListAdapter
    }

    fun doRepoSearch(){
        loadingIndicator.visibility = View.VISIBLE
        searchResultsListRV.visibility = View.INVISIBLE
        searchErrorTV.visibility = View.INVISIBLE

        weatherService.searchAPI(location)
            .enqueue(object : Callback<ForecastPeriod>{
                override fun onResponse(call: Call<ForecastPeriod>, response: Response<ForecastPeriod>) {
                    Log.d(TAG, "Response received for query '$location', status code: ${response.code()}")
                    loadingIndicator.visibility = View.INVISIBLE
                    if (response.isSuccessful) {
                        repoListAdapter.updateRepoList(response.body()?.list)
                        searchResultsListRV.visibility = View.VISIBLE
                    } else {
                        searchErrorTV.visibility = View.VISIBLE
                        searchErrorTV.text = getString(R.string.search_error)
                    }
                }

                override fun onFailure(call: Call<ForecastPeriod>, t: Throwable) {
                    Log.d(TAG, "Error executing query '$location': ${t.message}")
                    loadingIndicator.visibility = View.INVISIBLE
                    searchErrorTV.visibility = View.VISIBLE
                    searchErrorTV.text = getString(R.string.search_error)
                }
            })
    }

    private fun onForecastPeriodClick(weather: ForecastPeriod) {
        val intent = Intent(this, WeatherDetailActivity::class.java).apply {
            putExtra(, weather)
        }
        startActivity(intent)
    }

    private data class ApiSearchResults(
        val list: List<ForecastPeriod>

    )

    /*
     * This function simply initializes a list of dummy weather data.  You won't need this anymore
     * once you start fetching data from the OpenWeather API.
     */
    /*
    private fun initForecastPeriods(): MutableList<ForecastPeriod> {
        return mutableListOf(
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 14,
                highTemp = 51,
                lowTemp = 43,
                pop = 0.25,
                shortDesc = "Mostly sunny",
                longDesc = "Mostly sunny with clouds increasing in the evening"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 15,
                highTemp = 55,
                lowTemp = 39,
                pop = 0.8,
                shortDesc = "AM showers",
                longDesc = "Morning showers receding in the afternoon, with patches of sun later in the day"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 16,
                highTemp = 47,
                lowTemp = 39,
                pop = 0.1,
                shortDesc = "AM fog/PM clouds",
                longDesc = "Cooler, with morning fog lifting into a cloudy day"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 17,
                highTemp = 53,
                lowTemp = 36,
                pop = 0.6,
                shortDesc = "AM showers",
                longDesc = "Chance of light rain in the morning"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 18,
                highTemp = 49,
                lowTemp = 33,
                pop = 0.1,
                shortDesc = "Partly cloudy",
                longDesc = "Early clouds clearing as the day goes on; nighttime temperatures approaching freezing"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 19,
                highTemp = 49,
                lowTemp = 36,
                pop = 0.15,
                shortDesc = "Partly cloudy",
                longDesc = "Clouds increasing throughout the day with periods of sun interspersed"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 20,
                highTemp = 48,
                lowTemp = 38,
                pop = 0.3,
                shortDesc = "Mostly cloudy",
                longDesc = "Cloudy all day, with a slight chance of rain late in the evening"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 21,
                highTemp = 45,
                lowTemp = 35,
                pop = 0.5,
                shortDesc = "Showers",
                longDesc = "Cooler with periods of rain throughout the day"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 22,
                highTemp = 45,
                lowTemp = 30,
                pop = 0.3,
                shortDesc = "AM showers",
                longDesc = "Cool with a chance of rain in the morning; nighttime temperatures just below freezing"
            ),
            ForecastPeriod(
                year = 2023,
                month = 0,
                day = 23,
                highTemp = 44,
                lowTemp = 31,
                pop = 0.5,
                shortDesc = "Few showers",
                longDesc = "Cool with a chance rain throughout the day; nighttime temperatures just below freezing"
            )
        )
    }
    */
}