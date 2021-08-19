package com.bios.serverack.ui.ip

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.navigation.fragment.findNavController
import com.bios.serverack.R
import com.bios.serverack.data.repository.Repository
import com.bios.serverack.databinding.FragmentIpBinding
import com.google.android.material.snackbar.Snackbar

class IPFragment : Fragment() {
    lateinit var ipBinding: FragmentIpBinding
    val repository = Repository()
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        ipBinding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_ip, container, false
        )

        ipBinding.serverButton.setOnClickListener {
            if (ipBinding.serverUrl.text.toString().isNotEmpty()) {
                if (ipBinding.serverUrl.text.toString().endsWith("/")) {
                    repository.setServerEndPoint(ipBinding.serverUrl.text.toString())
                    this.findNavController()
                        .navigate(IPFragmentDirections.actionIPFragmentToLoginFragment())
                } else {
                    showSnackBar("Please make sure the server url endswith /")
                }
            } else {
                showSnackBar("Please enter the server URL")
            }
        }


        return ipBinding.root
    }

    fun showSnackBar(msg: String, len: Int = Snackbar.LENGTH_SHORT) {
        Snackbar.make(ipBinding.root, msg, len)
            .show()
    }
}