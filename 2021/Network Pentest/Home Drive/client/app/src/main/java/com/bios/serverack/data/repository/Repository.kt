package com.bios.serverack.data.repository

import android.app.Application
import android.app.DownloadManager
import android.content.Context
import android.content.SharedPreferences
import android.net.Uri
import android.util.Log
import com.bios.serverack.BiosApplication
import com.bios.serverack.R
import com.bios.serverack.data.model.Signup
import com.bios.serverack.data.model.User
import com.bios.serverack.data.remote.ServiceBuilder.retrofitService
import android.os.Environment
import com.bios.serverack.BuildConfig


class Repository {
    private val networkService by lazy {
        retrofitService
    }
    private val application: Application = BiosApplication.instance

    private val sharedPref: SharedPreferences by lazy {
        application.getSharedPreferences(
            application.getString(R.string.preference_file_key), Context.MODE_PRIVATE
        )
    }


    suspend fun doLoginService(user: User): String {
        Log.i("TAG", "doLoginService: ")
        return networkService.doLoginAsync(user)
    }

    suspend fun isUserAdmin(): String {
        return networkService.isAdmin(getJWTToken()!!)
    }

    suspend fun doSignUpService(signup: Signup): String {
        return networkService.doSignUp(signup)
    }

    suspend fun getFilesFromServer(): String? {
        return getJWTToken()?.let { networkService.getAllFiles(it) }
    }


    fun saveJWTToken(token: String) {
        sharedPref.edit().putString(application.getString(R.string.jwt_token), token).apply()
    }

    fun getJWTToken() =
        sharedPref.getString(application.getString(R.string.jwt_token), "")


    fun setServerEndPoint(token: String) {
        sharedPref.edit().putString(application.getString(R.string.server_end_point), token).apply()
    }

    fun getServerEndPoint() =
        sharedPref.getString(application.getString(R.string.server_end_point), "")

    suspend fun deleteFile(filename: String): String {
        return networkService.deleteFile(getJWTToken()!!, filename)
    }

//    suspend fun downloadFile(filename: String): Response<ResponseBody> {
//        return networkService.downloadFile(getJWTToken()!!, filename)
//    }

    public fun downloadFile(fileName: String): Long {
        // fileName -> fileName with extension
        val url = "${getServerEndPoint()}download/{$fileName}"
        val request = DownloadManager.Request(Uri.parse(url))
            .addRequestHeader("x-access-token", getJWTToken())
            .setAllowedNetworkTypes(DownloadManager.Request.NETWORK_WIFI or DownloadManager.Request.NETWORK_MOBILE)
            .setTitle(fileName)
            .setDescription(fileName)
            .setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED)
            .setAllowedOverMetered(true)
            .setAllowedOverRoaming(false)
            .setDestinationInExternalPublicDir(Environment.DIRECTORY_DOWNLOADS, fileName)
        val downloadManager =
            application.getSystemService(Context.DOWNLOAD_SERVICE) as DownloadManager
        return downloadManager.enqueue(request)
    }
}