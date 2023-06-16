package com.example.myapplication_final

import android.app.SearchManager
import android.content.ActivityNotFoundException
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.android.material.snackbar.Snackbar

class BookmarkedActivitiesActivity: AppCompatActivity() {
    private val viewModel: BookmarkedActivitiesViewModel by viewModels()
    private val activityListAdapter = ActivityListAdapter(::learnMore, ::bookmarkActivity)
    private lateinit var bookmarkedActivitiesRV: RecyclerView
    val tag = "BOOKMARK ACTIVITY"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_bookmarked_activities)


        bookmarkedActivitiesRV = findViewById(R.id.rv_bookmarked_activities)
        bookmarkedActivitiesRV.layoutManager = LinearLayoutManager(this)
        bookmarkedActivitiesRV.setHasFixedSize(true)
        bookmarkedActivitiesRV.adapter = this.activityListAdapter

        viewModel.bookmarkedActivities.observe(this){bookmarkedActivities ->
            activityListAdapter.updateActivityList(bookmarkedActivities)
            /*for(entry in bookmarkedActivities){
                val btn = findViewById<Button>(R.id.bookmark)
                btn.text = "Remove"
            }*/
        }

        val backButton = findViewById<Button>(R.id.backButton)
        backButton.setOnClickListener {
            goBack()
        }

    }

    private fun learnMore(query:String){
        val intent = Intent(Intent.ACTION_WEB_SEARCH).apply{
            putExtra(SearchManager.QUERY, query)
        }
        try{
            startActivity(intent)
        } catch (e: ActivityNotFoundException) {
            Snackbar.make(
                findViewById(R.id.linear_layout),
                R.string.failed_web_search,
                Snackbar.LENGTH_LONG
            ).show()
        }
    }

    private fun bookmarkActivity(data:BoredData){
        if(data.num == 1){
            data.num = 0
            viewModel.deleteBookmarkedActivity(data)
        }
        else if(data.num == 0){
            data.num = 1
            viewModel.addBookmarkedActivity(data)
        }
    }

    private fun goBack() {
        val intent = Intent(this, MainActivity::class.java)
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP)
        startActivity(intent)
    }
}