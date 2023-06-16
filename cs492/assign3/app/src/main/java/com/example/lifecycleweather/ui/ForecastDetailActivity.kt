package com.example.lifecycleweather.ui

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.ImageView
import android.widget.TextView
import com.bumptech.glide.Glide
import com.example.lifecycleweather.R
import com.example.lifecycleweather.data.ForecastCity
import com.example.lifecycleweather.data.ForecastPeriod
import com.example.lifecycleweather.util.openWeatherEpochToDate

const val EXTRA_FORECAST_PERIOD = "com.example.android.lifecycleweather.FORECAST_PERIOD"
const val EXTRA_FORECAST_CITY = "com.example.android.lifecycleweather.FORECAST_CITY"

class ForecastDetailActivity : AppCompatActivity() {
    private var forecastCity: ForecastCity? = null
    private var forecastPeriod: ForecastPeriod? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_forecast_detail)

        /*
         * If an intent was used to launch this activity and it contains information about a
         * forecast city, use that information to populate the UI.
         */
        if (intent != null && intent.hasExtra(EXTRA_FORECAST_CITY)) {
            forecastCity = intent.getSerializableExtra(EXTRA_FORECAST_CITY) as ForecastCity
            findViewById<TextView>(R.id.tv_forecast_city).text = forecastCity!!.name
        }

        /*
         * If an intent was used to launch this activity and it contains information about a
         * forecast period, use that information to populate the UI.
         */
        if (intent != null && intent.hasExtra(EXTRA_FORECAST_PERIOD)) {
            forecastPeriod = intent.getSerializableExtra(EXTRA_FORECAST_PERIOD) as ForecastPeriod

            Glide.with(this)
                .load(forecastPeriod!!.iconUrl)
                .into(findViewById(R.id.iv_forecast_icon))

            findViewById<TextView>(R.id.tv_forecast_date).text = getString(
                R.string.forecast_date_time,
                openWeatherEpochToDate(forecastPeriod!!.epoch, forecastCity!!.tzOffsetSec)
            )

            findViewById<TextView>(R.id.tv_low_temp).text =
                getString(R.string.forecast_temp, forecastPeriod!!.lowTemp, "F")

            findViewById<TextView>(R.id.tv_high_temp).text =
                getString(R.string.forecast_temp, forecastPeriod!!.highTemp, "F")

            findViewById<TextView>(R.id.tv_pop).text =
                getString(R.string.forecast_pop, forecastPeriod!!.pop)

            findViewById<TextView>(R.id.tv_clouds).text =
                getString(R.string.forecast_clouds, forecastPeriod!!.cloudCover)

            findViewById<TextView>(R.id.tv_wind).text =
                getString(R.string.forecast_wind, forecastPeriod!!.windSpeed, "MPH")

            findViewById<ImageView>(R.id.iv_wind_dir).rotation =
                forecastPeriod!!.windDirDeg.toFloat()

            findViewById<TextView>(R.id.tv_forecast_description).text =
                forecastPeriod!!.description
        }
    }

    /**
     * This method adds a custom menu to the action bar for this activity.
     */
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.activity_forecast_detail, menu)
        return true
    }

    /**
     * This method is called when the user selects an action from the action bar.
     */
    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.action_share -> {
                shareForecastText()
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }

    /**
     * This method launches the Android Sharesheet to allow the user to share information about
     * this forecast period.
     */
    private fun shareForecastText() {
        if (forecastCity != null && forecastPeriod != null) {
            /*
             * The shared text is complex!
             */
            val date = openWeatherEpochToDate(forecastPeriod!!.epoch, forecastCity!!.tzOffsetSec)
            val shareText = getString(
                R.string.share_forecast_text,
                getString(R.string.app_name),
                forecastCity!!.name,
                getString(R.string.forecast_date_time, date),
                forecastPeriod!!.description,
                getString(R.string.forecast_temp, forecastPeriod!!.highTemp, "F"),
                getString(R.string.forecast_temp, forecastPeriod!!.lowTemp, "F"),
                getString(R.string.forecast_pop, forecastPeriod!!.pop)
            )

            val intent = Intent().apply {
                action = Intent.ACTION_SEND
                putExtra(Intent.EXTRA_TEXT, shareText)
                type = "text/plain"
            }
            startActivity(Intent.createChooser(intent, null))
        }
    }
}