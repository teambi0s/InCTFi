package com.bios.serverack.data.remote

import com.bios.serverack.data.model.Signup
import com.bios.serverack.data.model.User
import com.bios.serverack.data.repository.Repository
import com.squareup.moshi.Moshi
import com.squareup.moshi.kotlin.reflect.KotlinJsonAdapterFactory
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import retrofit2.Retrofit
import retrofit2.converter.moshi.MoshiConverterFactory
import retrofit2.converter.scalars.ScalarsConverterFactory
import retrofit2.http.*
import java.util.concurrent.TimeUnit


val API_POINT = Repository().getServerEndPoint()


var logging = HttpLoggingInterceptor()

private val moshi = Moshi.Builder()
    .add(KotlinJsonAdapterFactory())
    .build()


var client = OkHttpClient.Builder()
    .connectTimeout(10, TimeUnit.SECONDS)
    .readTimeout(30, TimeUnit.SECONDS)
    .addInterceptor(logging.setLevel(HttpLoggingInterceptor.Level.BODY))
    .build()


private val retrofit = Retrofit.Builder()
    .baseUrl(API_POINT) // change this IP for testing by your actual machine IP
    .addConverterFactory(ScalarsConverterFactory.create())
    .addConverterFactory(MoshiConverterFactory.create(moshi))
    .client(client)
    .build()

interface NetworkService {

    @Headers("Content-Type: application/json")
    @POST("login")
    suspend fun doLoginAsync(@Body user: User): String


    @Headers("Content-Type: application/json")
    @POST("register")
    suspend fun doSignUp(@Body signup: Signup): String

    @Headers("Content-Type: application/json")
    @GET("list")
    suspend fun getAllFiles(@Header("x-access-token") token: String): String


    @POST("delete/{filename}")
    suspend fun deleteFile(
        @Header("x-access-token") token: String,
        @Path("filename") filename: String
    ): String

    @GET("isAdmin")
    suspend fun isAdmin(
        @Header("x-access-token") token: String,
    ): String


}

object ServiceBuilder {
    val retrofitService: NetworkService by lazy {
        retrofit.create(NetworkService::class.java)
    }
}