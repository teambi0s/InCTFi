package com.bios.serverack

import android.util.Log
import androidx.databinding.BindingAdapter
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.bios.serverack.data.model.Message
import com.bios.serverack.ui.files.FilesAdapter

@BindingAdapter("setFilesAdapter")
fun setFilesAdapter(recyclerView: RecyclerView, items: List<Message>) {
    Log.i("TAG", "setFilesAdapter: ${items.size}")
    (recyclerView.adapter as FilesAdapter).submitList(items)
    recyclerView.apply {
        layoutManager = LinearLayoutManager(recyclerView.context)
    }
}