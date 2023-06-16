package com.example.myapplication_final

import android.app.SearchManager
import android.content.ActivityNotFoundException
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import androidx.activity.viewModels
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.android.material.snackbar.Snackbar
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

const val BASE_URL = "https://www.boredapi.com/api/"

class MainActivity : AppCompatActivity() {
    private lateinit var activityResultsListRV : RecyclerView
    private val activityListAdapter = ActivityListAdapter(::learnMore, ::bookmarkActivity)
    val TAG = "Activity Main"

    private val viewModel: BookmarkedActivitiesViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //https://www.boredapi.com/api/activity

        val searchButton: Button = findViewById(R.id.btnToGetActivity)

        searchButton.setOnClickListener{
            getData()
        }

        val calendarButton = findViewById<Button>(R.id.calendar_button)
        calendarButton.setOnClickListener {
            val intent = Intent(this, CalendarActivity::class.java)
            startActivity(intent)
        }

        val bookmarkButton = findViewById<Button>(R.id.bookmark_button)
        bookmarkButton.setOnClickListener{
            val intent = Intent(this, BookmarkedActivitiesActivity::class.java)
            startActivity(intent)
        }

        activityResultsListRV = findViewById(R.id.recyclerview)
        activityResultsListRV.layoutManager = LinearLayoutManager(this)
        activityResultsListRV.setHasFixedSize(false)
        activityResultsListRV.adapter = activityListAdapter


    }

    private fun getData() {
        val retroFitBuilder = Retrofit.Builder()
            .addConverterFactory(GsonConverterFactory.create())
            .baseUrl(BASE_URL)
            .build()
            .create(APInterface::class.java)

        val retrofitReturnData = retroFitBuilder.getData()

        retrofitReturnData.enqueue(object : Callback<BoredData?> {
            override fun onResponse(call: Call<BoredData?>, response: Response<BoredData?>) {
                val responseBody = response.body()!!
                if(response.isSuccessful){
                    activityListAdapter.addActivity(responseBody)
                } else {
                    Log.d(TAG, "Not successful")
                }

            }

            override fun onFailure(call: Call<BoredData?>, t: Throwable) {
                Log.d(TAG,"onFailure: " + t.message)
            }
        })
    }



    private fun learnMore(query:String){
        val intent = Intent(Intent.ACTION_WEB_SEARCH).apply{
            putExtra(SearchManager.QUERY, query)
        }
        try{
            startActivity(intent)
        } catch (e:ActivityNotFoundException) {
            Snackbar.make(
                findViewById(R.id.linear_layout),
                R.string.failed_web_search,
                Snackbar.LENGTH_LONG
            ).show()
        }
    }

    private fun bookmarkActivity(data:BoredData){
        val btn = findViewById<Button>(R.id.bookmark)
        if(data.num == 1){
            data.num = 0
            viewModel.deleteBookmarkedActivity(data)
            btn.text = "Bookmark"
        }
        else if(data.num == 0){
            data.num = 1
            viewModel.addBookmarkedActivity(data)
            btn.text = "Remove"
        }
    }
}
