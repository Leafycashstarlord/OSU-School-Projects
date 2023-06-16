package com.example.myapplication_final

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class ActivityListAdapter(
    private val learnMoreClick: (String) -> Unit,
    private val bookmarkClick: (BoredData) -> Unit
) : RecyclerView.Adapter<ActivityListAdapter.ActivityListViewHolder>(){
    private var activityList = mutableListOf<BoredData>()

    fun updateActivityList(newActList: List<BoredData>){
        activityList = newActList as MutableList<BoredData>
        notifyDataSetChanged()
    }

    fun addActivity(newActivity: BoredData){
        activityList.add(newActivity)
        notifyDataSetChanged()
    }

    override fun getItemCount() = activityList.size

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ActivityListViewHolder {
        val itemView = LayoutInflater.from(parent.context)
            .inflate(R.layout.activity_list_item, parent, false)
        return ActivityListViewHolder(itemView, learnMoreClick, bookmarkClick)
    }

    override fun onBindViewHolder(holder: ActivityListViewHolder, position: Int) {
        holder.bind(activityList[position])
    }

    class ActivityListViewHolder (
        itemView: View,
        private val onLearnClick: (String) -> Unit,
        private val onBookmarkClick: (BoredData) -> Unit
    ): RecyclerView.ViewHolder(itemView) {
        private var currentActivity:BoredData? = null
        private val activityName: TextView = itemView.findViewById(R.id.activity_name)

        init{
            itemView.findViewById<Button>(R.id.learn_more).setOnClickListener{
                onLearnClick(currentActivity!!.activity)
            }

            itemView.findViewById<Button>(R.id.bookmark).setOnClickListener{
                onBookmarkClick(currentActivity!!)
            }

        }

        fun bind(activity:BoredData){
            currentActivity=activity
            activityName.text = activity.activity
        }
    }


}