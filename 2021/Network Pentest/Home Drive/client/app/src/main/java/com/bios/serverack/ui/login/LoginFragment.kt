package com.bios.serverack.ui.login

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.viewModels
import androidx.navigation.fragment.findNavController
import com.bios.serverack.R
import com.bios.serverack.Utils
import com.bios.serverack.databinding.FragmentLoginBinding
import com.google.android.material.snackbar.Snackbar

class LoginFragment : Fragment() {

    val loginViewModel: LoginViewModel by viewModels()
    lateinit var loginBinding: FragmentLoginBinding

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {

        loginBinding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_login, container, false
        )

        loginBinding.loginButton.setOnClickListener {
            activity?.let { it1 -> loginViewModel.hideKeyboardFrom(it1, loginBinding.root) }
            if (Utils.isNetworkAvailable(requireActivity())) {
                if (!isEmpty()) {
                    val username = loginBinding.usernameEdittext.text.toString()
                    val password = loginBinding.passwordEdittext.text.toString()
                    loginViewModel.doLogin(username, password)
                }
            } else {
                showSnackBar("Please connect to internet")
            }
        }


        loginViewModel.doLogin.observe(viewLifecycleOwner, {
            if (it) {
                this.findNavController()
                    .navigate(LoginFragmentDirections.actionLoginFragmentToFilesFragment())
            }
        })

        loginViewModel.messageHandler.observe(viewLifecycleOwner, {
            if (it.isNotEmpty()) {
                showSnackBar(it)
            }
        })

        loginBinding.createAccount.setOnClickListener {
            this.findNavController()
                .navigate(LoginFragmentDirections.actionLoginFragmentToSignupFragment())
        }

        return loginBinding.root
    }

    private fun isEmpty(): Boolean {

        if (loginBinding.usernameEdittext.text.isEmpty() &&
            loginBinding.passwordEdittext.text.isEmpty()
        ) {
            loginBinding.userNameTextInputLayout.error = "Username is empty"
            loginBinding.passwordTextInputLayout.error = "Password is empty"
            return true
        }

        if (loginBinding.usernameEdittext.text.isEmpty()) {
            loginBinding.userNameTextInputLayout.error = "Username is empty"
            return true
        }

        if (loginBinding.passwordEdittext.text.isEmpty()) {
            loginBinding.passwordTextInputLayout.error = "Password is empty"
            return true
        }
        return false
    }

    fun showSnackBar(msg: String, len: Int = Snackbar.LENGTH_SHORT) {
        Snackbar.make(loginBinding.root, msg, len)
            .show()
    }
}