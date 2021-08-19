package com.bios.serverack

import android.app.Application
import android.app.NotificationChannel
import android.app.NotificationManager
import android.content.Context
import android.os.Build
import net.gotev.uploadservice.UploadServiceConfig

class BiosApplication : Application() {

    companion object {
        lateinit var instance: Application
        const val notificationChannelID = "BiosApp"
    }

    override fun onCreate() {
        super.onCreate()
        instance = this
        createNotificationChannel()
        UploadServiceConfig.initialize(
            context = this,
            defaultNotificationChannel = notificationChannelID,
            debug = BuildConfig.DEBUG
        )

    }


    private fun createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= 26) {
            val channel = NotificationChannel(
                Companion.notificationChannelID,
                "BiosApplication",
                NotificationManager.IMPORTANCE_LOW
            )
            val manager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
            manager.createNotificationChannel(channel)
        }
    }
}