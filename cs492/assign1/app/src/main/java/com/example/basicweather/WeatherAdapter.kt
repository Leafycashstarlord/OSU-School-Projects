package com.example.basicweather

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.google.android.material.snackbar.Snackbar


class WeatherAdapter: RecyclerView.Adapter<WeatherAdapter.WeatherViewHolder>() {
    val weatherList:MutableList<Weather> = mutableListOf()

    override fun getItemCount() = weatherList.size

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): WeatherViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R. layout.weather_list_item, parent, false)
        return WeatherViewHolder(view)
    }

    override fun onBindViewHolder(holder: WeatherViewHolder, position: Int) {
        holder.bind(weatherList[position])
    }

    fun addWeather(weather: Weather){
        weatherList.add(0, weather)
        notifyItemInserted(0)
    }

    class WeatherViewHolder(view: View): RecyclerView.ViewHolder(view){
        private val date: TextView = view.findViewById(R.id.weather_date)
        private val high: TextView = view.findViewById(R.id.weather_high)
        private val low: TextView = view.findViewById(R.id.weather_low)
        private val precip: TextView = view.findViewById(R.id.weather_precip)
        private val descShort: TextView = view.findViewById(R.id.weather_short)
        private var descLong: String = ""

        init {
            view.setOnClickListener{
                val snackbar = Snackbar.make(view, this.descLong, Snackbar.LENGTH_SHORT).show()
            }
        }

        fun bind (weather: Weather) {
            this.date.text = weather.date
            this.high.text = weather.high
            this.low.text = weather.low
            this.precip.text = weather.precip
            this.descShort.text = weather.descShort
            this.descLong = weather.descLong
        }
    }
}