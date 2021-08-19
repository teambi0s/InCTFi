package com.bios.serverack.ui.signup

import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.bios.serverack.data.model.Signup
import com.bios.serverack.data.repository.Repository
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.launch
import org.json.JSONObject
import java.lang.Exception
import android.app.Activity
import android.content.Context
import android.view.View
import android.view.inputmethod.InputMethodManager


class SignUpViewModel : ViewModel() {
    private val viewModelJob = SupervisorJob()
    private val viewModelScope = CoroutineScope(viewModelJob + Dispatchers.Main)
    private val repository = Repository()
    private val message = MutableLiveData("")
    val doSignUp = MutableLiveData<String>()


    fun doSignUp(username: String, password: String, email: String) {
        viewModelScope.launch {
            val signup = try {
                repository.doSignUpService(Signup(username, email, password))
            } catch (e: Exception) {
                e.printStackTrace()
                ""
            }
            try {
                doSignUp.value = JSONObject(signup).getString("message")
            } catch (e: Exception) {
                e.printStackTrace()
                doSignUp.value = "Is your Internet On ?"
            }
        }
    }

    fun hideKeyboardFrom(context: Context, view: View) {
        val imm: InputMethodManager =
            context.getSystemService(Activity.INPUT_METHOD_SERVICE) as InputMethodManager
        imm.hideSoftInputFromWindow(view.getWindowToken(), 0)
    }
}