package com.example.roomyweather.ui

import android.content.ActivityNotFoundException
import android.content.Intent
import android.content.SharedPreferences
import android.content.SharedPreferences.Editor
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.TextView
import androidx.activity.viewModels
import androidx.drawerlayout.widget.DrawerLayout
import androidx.lifecycle.LiveData
import androidx.navigation.NavController
import androidx.navigation.findNavController
import androidx.navigation.fragment.NavHostFragment
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.navigateUp
import androidx.navigation.ui.setupActionBarWithNavController
import androidx.navigation.ui.setupWithNavController
import androidx.preference.PreferenceManager
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
//import com.example.roomyweather.BuildConfig
import com.example.roomyweather.R
import com.example.roomyweather.data.ForecastPeriod
import com.example.roomyweather.data.RoomEntity
import com.google.android.material.navigation.NavigationView
import com.google.android.material.progressindicator.CircularProgressIndicator
import com.google.android.material.snackbar.Snackbar
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.count

/*
 * Often, we'll have sensitive values associated with our code, like API keys, that we'll want to
 * keep out of our git repo, so random GitHub users with permission to view our repo can't see them.
 * The OpenWeather API key is like this.  We can keep our API key out of source control using the
 * technique described below.  Note that values configured in this way can still be seen in the
 * app bundle installed on the user's device, so this isn't a safe way to store values that need
 * to be kept secret at all costs.  This will only keep
 *
 * To use your own OpenWeather API key here, create a file called `gradle.properties` in your
 * GRADLE_USER_HOME directory (this will usually be `$HOME/.gradle/` in MacOS/Linux and
 * `$USER_HOME/.gradle/` in Windows), and add the following line:
 *
 *   OPENWEATHER_API_KEY="<put_your_own_OpenWeather_API_key_here>"
 *
 * Then, add the following line to the `defaultConfig` section of build.gradle:
 *
 *   buildConfigField("String", "OPENWEATHER_API_KEY", OPENWEATHER_API_KEY)
 *
 * The Gradle build for this project will grab that value and store it in the field
 * `BuildConfig.OPENWEATHER_API_KEY` that's used below.  You can read more about this setup on the
 * following pages:
 *
 *   https://developer.android.com/studio/build/gradle-tips#share-custom-fields-and-resource-values-with-your-app-code
 *
 *   https://docs.gradle.org/current/userguide/build_environment.html#sec:gradle_configuration_properties
 *
 * Alternatively, if you don't mind whether people see your OpenWeather API key on GitHub, you can
 * just hard-code your API key below, replacing `BuildConfig.OPENWEATHER_API_KEY` 🤷‍.
 */
const val OPENWEATHER_APPID = "5d181e7ecbf80f51a8c06f1b5929911b"

class MainActivity : AppCompatActivity() {
    private lateinit var appBarConfiguration: AppBarConfiguration
    private val citiesViewModel: BookmarkedCitiesViewModel by viewModels()
    private val fiveDayForecastViewModel: FiveDayForecastViewModel by viewModels()


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val navHostFragment = supportFragmentManager.findFragmentById(
            R.id.nav_host_fragment
        ) as NavHostFragment
        val navController = navHostFragment.navController
        val drawerLayout: DrawerLayout = findViewById(R.id.drawer_layout)

        appBarConfiguration = AppBarConfiguration(navController.graph, drawerLayout)
        setupActionBarWithNavController(navController, appBarConfiguration)
        findViewById<NavigationView>(R.id.nav_view).setupWithNavController(navController)
    }

    override fun onResume() {
        super.onResume()
        citiesViewModel.cities.observe(this){
            addCityToDrawer(it)
        }

    }

    override fun onSupportNavigateUp(): Boolean {
        val navController = findNavController(R.id.nav_host_fragment)
        return navController.navigateUp(appBarConfiguration) || super.onSupportNavigateUp()
    }

    private fun addCityToDrawer(database: List<RoomEntity>){
        val navView: NavigationView = findViewById(R.id.nav_view)
        val citySubMenu = navView.menu.findItem(R.id.city_submenu).subMenu
        citySubMenu?.clear()
        for (entry in database){
            citySubMenu?.add(entry.location)?.setOnMenuItemClickListener {
                val cityEntity = RoomEntity(entry.location!!, System.currentTimeMillis())
                citiesViewModel.addCity(cityEntity)

                val sharedPrefs = PreferenceManager.getDefaultSharedPreferences(this)
                with(sharedPrefs.edit()){
                    putString(getString(R.string.pref_city_key), entry.location)
                    apply()
                }

                fiveDayForecastViewModel.loadFiveDayForecast(
                    entry.location,
                    sharedPrefs.getString(getString(R.string.pref_units_key), null),
                    OPENWEATHER_APPID
                )

                val navController = findNavController(R.id.nav_host_fragment)
                navController.navigate(R.id.forecast_list)

                findViewById<DrawerLayout>(R.id.drawer_layout).closeDrawers()

                true
            }
        }
    }
}