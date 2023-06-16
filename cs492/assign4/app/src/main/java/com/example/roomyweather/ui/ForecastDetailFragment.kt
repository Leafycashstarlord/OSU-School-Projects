package com.example.roomyweather.ui

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuInflater
import android.view.MenuItem
import android.view.View
import android.widget.ImageView
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.navArgs
import androidx.preference.PreferenceManager
import com.bumptech.glide.Glide
import com.example.roomyweather.R
import com.example.roomyweather.data.ForecastCity
import com.example.roomyweather.data.ForecastPeriod
import com.example.roomyweather.util.getTempUnitsDisplay
import com.example.roomyweather.util.getWindSpeedUnitsDisplay
import com.example.roomyweather.util.openWeatherEpochToDate

const val EXTRA_FORECAST_PERIOD = "com.example.android.roomyweather.FORECAST_PERIOD"
const val EXTRA_FORECAST_CITY = "com.example.android.roomyweather.FORECAST_CITY"

class ForecastDetailFragment : Fragment(R.layout.forecast_detail_fragment) {
    private var forecastCity: ForecastCity? = null
    private var forecastPeriod: ForecastPeriod? = null

    private val args: ForecastDetailFragmentArgs by navArgs()

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setHasOptionsMenu(true)

        forecastCity = args.city
        forecastPeriod = args.forecastPeriod

        /*
         * Figure out the correct temperature and wind units to display for the current
         * setting of the units preference.
         */
        val sharedPrefs = PreferenceManager.getDefaultSharedPreferences(requireContext())
        val units = sharedPrefs.getString(getString(R.string.pref_units_key), null)
        val tempUnitsDisplay = getTempUnitsDisplay(units, requireContext())
        val windUnitsDisplay = getWindSpeedUnitsDisplay(units, requireContext())

        Glide.with(this)
            .load(forecastPeriod!!.iconUrl)
            .into(view.findViewById(R.id.iv_forecast_icon))

        view.findViewById<TextView>(R.id.tv_forecast_date).text = getString(
            R.string.forecast_date_time,
            openWeatherEpochToDate(forecastPeriod!!.epoch, forecastCity!!.tzOffsetSec)
        )

        view.findViewById<TextView>(R.id.tv_low_temp).text = getString(
            R.string.forecast_temp,
            forecastPeriod!!.lowTemp,
            tempUnitsDisplay
        )

        view.findViewById<TextView>(R.id.tv_high_temp).text = getString(
            R.string.forecast_temp,
            forecastPeriod!!.highTemp,
            tempUnitsDisplay
        )

        view.findViewById<TextView>(R.id.tv_pop).text =
            getString(R.string.forecast_pop, forecastPeriod!!.pop)

        view.findViewById<TextView>(R.id.tv_clouds).text =
            getString(R.string.forecast_clouds, forecastPeriod!!.cloudCover)

        view.findViewById<TextView>(R.id.tv_wind).text = getString(
            R.string.forecast_wind,
            forecastPeriod!!.windSpeed,
            windUnitsDisplay
        )

        view.findViewById<ImageView>(R.id.iv_wind_dir).rotation =
            forecastPeriod!!.windDirDeg.toFloat()

        view.findViewById<TextView>(R.id.tv_forecast_description).text =
            forecastPeriod!!.description
    }

    /**
     * This method adds a custom menu to the action bar for this activity.
     */
    override fun onCreateOptionsMenu(menu: Menu, menuInflater: MenuInflater) {
        menuInflater.inflate(R.menu.activity_forecast_detail, menu)
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