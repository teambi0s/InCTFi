package com.bios.serverack.ui.upload

import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.bios.serverack.data.repository.Repository
import kotlinx.coroutines.*
import org.json.JSONObject
import java.lang.Exception

class UploadViewModel : ViewModel() {
    private val repository = Repository()
    private val viewModelJob = SupervisorJob()
    private val viewModelScope = CoroutineScope(viewModelJob + Dispatchers.Main)
    fun getToken() = repository.getJWTToken()
    var isAdminLiveData = MutableLiveData<Boolean>()


    fun checkUserIsAdmin() {
        viewModelScope.launch {
            val isAdmin = try {
                repository.isUserAdmin()
            } catch (e: Exception) {
                e.printStackTrace()
                ""
            }

            if (isAdmin.isNotEmpty()) {
                val admin = JSONObject(isAdmin).getInt("status_code");
                isAdminLiveData.value = admin == 200
            }
        }
    }
}