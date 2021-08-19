package com.bios.serverack.ui.files

import android.util.Log
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.bios.serverack.Utils
import com.bios.serverack.data.model.Message
import com.bios.serverack.data.repository.Repository
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.launch
import okhttp3.ResponseBody
import org.json.JSONObject

class FilesViewModel : ViewModel() {

    private val viewModelJob = SupervisorJob()
    private val viewModelScope = CoroutineScope(viewModelJob + Dispatchers.Main)
    private val repository = Repository()
    val networkHandler = MutableLiveData(false)
    val messageHandler = MutableLiveData("")
    val messageData = MutableLiveData<List<Message>>()

    init {
        messageData.value = emptyList()
        messageHandler.value = ""
        networkHandler.value = false
    }

    fun getFilesDataFromServer() {
        messageData.value = emptyList()
        Log.i("TAG", "getFilesDataFromServer: ")
        viewModelScope.launch {
            val filesData: String? = try {
                repository.getFilesFromServer()
            } catch (e: Exception) {
                e.printStackTrace()
                Log.i("TAG", "getFilesDataFromServer: " + e.printStackTrace())
                ""
            }
            if (!filesData.toString().contains("This user has no files.")) {
                val dataList = filesData?.let { Utils.filesDataConverter(it) }
                messageData.value = dataList!!
                networkHandler.value = true
            } else {
                messageHandler.value = JSONObject(filesData).getString("message")
                networkHandler.value = true
            }
        }
    }

    fun deleteFile(message: Message) {
        viewModelScope.launch {
            var deleteFile = try {
                repository.deleteFile(message.filename)
            } catch (e: Exception) {
                e.printStackTrace()
                ""
            }

            if (JSONObject(deleteFile).getString("message") == "Successfully deleted!") {
                messageHandler.value = JSONObject(deleteFile).getString("message")
                getFilesDataFromServer()
            } else {
                messageHandler.value = JSONObject(deleteFile).getString("message")
            }
        }
    }

    fun downloadFile(message: Message) {
        val id = repository.downloadFile(message.filename)
        messageHandler.value = "Downloading {${message.filename}}"
    }


}