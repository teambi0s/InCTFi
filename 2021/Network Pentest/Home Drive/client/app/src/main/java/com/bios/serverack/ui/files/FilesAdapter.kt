package com.bios.serverack.ui.files


import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.bios.serverack.data.model.Message
import com.bios.serverack.databinding.FileItemsBinding

class FilesAdapter(private val onClickListener: OnClickListener) :
    ListAdapter<Message, FileViewHolder>(FileItemCallBack()) {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): FileViewHolder {
        return FileViewHolder.from(parent)
    }

    override fun onBindViewHolder(holder: FileViewHolder, position: Int) {
        val item = getItem(position)
        holder.bind(item, onClickListener)
    }

    class OnClickListener(val clickListener: (message: Message, view: View) -> Unit) {
        fun onClick(message: Message, view: View) = clickListener(message, view)
    }
}

class FileViewHolder(val binding: FileItemsBinding) : RecyclerView.ViewHolder(binding.root) {
    fun bind(item: Message, onClickListener: FilesAdapter.OnClickListener) = with(binding) {
        binding.message = item
        binding.deleteButton.setOnClickListener {
            onClickListener.onClick(item, binding.deleteButton)
        }
        binding.downloadButton.setOnClickListener {
            onClickListener.onClick(item, binding.downloadButton)
        }
        Log.i("TAG", "bind:${item.filename} ")
        binding.executePendingBindings()
    }

    companion object {
        fun from(parent: ViewGroup): FileViewHolder {
            val layoutInflater = LayoutInflater.from(parent.context)
            val binding = FileItemsBinding.inflate(layoutInflater, parent, false)
            return FileViewHolder(binding)
        }
    }
}


class FileItemCallBack : DiffUtil.ItemCallback<Message>() {
    override fun areItemsTheSame(oldItem: Message, newItem: Message): Boolean {
        return oldItem.id == oldItem.id
    }

    override fun areContentsTheSame(oldItem: Message, newItem: Message): Boolean {
        return oldItem == newItem
    }


}

