package com.bios.serverack.ui.files

import android.Manifest
import android.os.Build
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.activity.result.contract.ActivityResultContracts
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.viewModels
import androidx.lifecycle.Observer
import androidx.navigation.fragment.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import com.bios.serverack.R
import com.bios.serverack.Utils
import com.bios.serverack.data.model.Message
import com.bios.serverack.databinding.FragmentFilesBinding
import com.google.android.material.snackbar.Snackbar


class FilesFragment : Fragment() {

    private val fileViewModel: FilesViewModel by viewModels()
    lateinit var filesBinding: FragmentFilesBinding
    private lateinit var filesAdapter: FilesAdapter
    private lateinit var message: Message
    private val checkPermission =
        registerForActivityResult(ActivityResultContracts.RequestMultiplePermissions()) {
            var count = 0
            for ((key, value) in it) {
                if (value) {
                    count++
                }
            }
            if (count >= 2)
                if (this::message.isInitialized)
                    fileViewModel.downloadFile(message)
        }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        filesBinding = DataBindingUtil.inflate(inflater, R.layout.fragment_files, container, false)
        fileViewModel.getFilesDataFromServer()

        fileViewModel.networkHandler.observe(viewLifecycleOwner, {
            if (!it) {
                filesBinding.filesProgressBar.visibility = View.VISIBLE
            } else {
                filesBinding.filesProgressBar.visibility = View.GONE
            }
        })

        fileViewModel.messageHandler.observe(viewLifecycleOwner, {
            it?.let { it1 ->
                if (it1.isNotEmpty()) {
                    showSnackBar(it1)
                } else {
                    showSnackBar("Loading data from server")
                }
            }
        })

        fileViewModel.messageData.observe(viewLifecycleOwner, {
            filesAdapter =
                FilesAdapter(FilesAdapter.OnClickListener { message: Message, view: View ->
                    if (Utils.isNetworkAvailable(requireActivity())) {
                        if (view.id == R.id.deleteButton) {
                            fileViewModel.deleteFile(message)
                        } else {
                            this.message = message
                            checkStoragePermissions()
                        }
                    } else {
                        showSnackBar("Please connect to the internet")
                    }
                })
            filesBinding.filesList.apply {
                adapter = filesAdapter
                setHasFixedSize(true)
                layoutManager = LinearLayoutManager(activity)
            }
            filesAdapter.submitList(it)


        })

        filesBinding.uploadFiles.setOnClickListener {
            this.findNavController()
                .navigate(FilesFragmentDirections.actionFilesFragmentToUploadFragment())
        }
        return filesBinding.root
    }


    private fun showSnackBar(msg: String, len: Int = Snackbar.LENGTH_SHORT) {
        Snackbar.make(filesBinding.root, msg, len)
            .show()
    }

    private fun checkStoragePermissions() {
        val permissions = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            arrayOf(
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.MANAGE_EXTERNAL_STORAGE
            )
        } else {
            arrayOf(
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE
            )
        }
        checkPermission.launch(permissions)
    }

}