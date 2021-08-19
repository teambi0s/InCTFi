package com.bios.serverack.ui.signup

import android.os.Bundle
import android.os.Handler
import android.os.Looper
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.viewModels
import androidx.navigation.fragment.findNavController
import com.bios.serverack.R
import com.bios.serverack.Utils
import com.bios.serverack.databinding.FragmentSignupBinding
import com.google.android.material.snackbar.Snackbar
import com.google.android.material.textfield.TextInputLayout

class SignupFragment : Fragment() {

    val signUpViewModel: SignUpViewModel by viewModels()
    lateinit var signupBinding: FragmentSignupBinding

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        // Inflate the layout for this fragment
        signupBinding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_signup,
            container, false
        )
        signupBinding.signInText.setOnClickListener {
            this.findNavController()
                .navigate(SignupFragmentDirections.actionSignupFragmentToLoginFragment())

        }

        signupBinding.signUpButton.setOnClickListener {
            if (Utils.isNetworkAvailable(requireActivity())) {
                if (validateData()) {
                    activity?.let { it1 ->
                        signUpViewModel.hideKeyboardFrom(
                            it1,
                            signupBinding.root
                        )
                    }
                    val username: String = signupBinding.usernameEdittext.text.toString()
                    val email: String = signupBinding.emailEditText.text.toString()
                    val password: String = signupBinding.passwordEdittext.text.toString()
                    signUpViewModel.doSignUp(username, password, email);
                }
            } else {
                showSnackBar("Please connect to internet")
            }
        }
        signUpViewModel.doSignUp.observe(viewLifecycleOwner, {
            when {
                it != "Username already in use!" -> {
                    showSnackBar(it, Snackbar.LENGTH_LONG)
                }
                it == "Is your Internet On ?" -> {
                    showSnackBar(it, Snackbar.LENGTH_LONG)
                }
                else -> {
                    showSnackBar(it, Snackbar.LENGTH_LONG)
                    Handler(Looper.getMainLooper()).postDelayed({
                        this.findNavController()
                            .navigate(SignupFragmentDirections.actionSignupFragmentToLoginFragment())
                    }, 3000)

                }
            }
        })


        return signupBinding.root
    }


    private fun validateData(): Boolean {
        val username: String = signupBinding.usernameEdittext.text.toString()
        val email: String = signupBinding.emailEditText.text.toString()
        val password: String = signupBinding.passwordEdittext.text.toString()
        val confirmPassword: String = signupBinding.confirmPasswordEditText.text.toString()
        val userNameTextInput: TextInputLayout = signupBinding.userNameTextInputLayout
        val emailTextInput: TextInputLayout = signupBinding.emailEditTextInput
        val passwordOneEditTextInput: TextInputLayout = signupBinding.passwordTextInputLayout
        val confirmPasswordEditInput: TextInputLayout = signupBinding.confirmPasswordTextInput

        if (username.isEmpty()) {
            userNameTextInput.error = "Enter Username"
            return false
        }
        if (email.isEmpty()) {
            emailTextInput.error = "Enter Email"
            return false
        }

        if (password.isEmpty()) {
            passwordOneEditTextInput.error = "Enter Password"
            return false
        }

        if (confirmPassword.isEmpty()) {
            confirmPasswordEditInput.error = "Enter Password"
            return false
        }

        if (password != confirmPassword) {
            showSnackBar("Passwords Does Not Match")
            return false
        }
        return true
    }


    fun showSnackBar(msg: String, len: Int = Snackbar.LENGTH_SHORT) {
        Snackbar.make(signupBinding.root, msg, len)
            .show()
    }

}