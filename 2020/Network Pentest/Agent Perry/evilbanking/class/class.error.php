<?php


class ErrorRep
{	
    function exist($code)
	{
		 $list = ["1A","2A","3A","4A","1B","2B","3B","4B","5B","6B","7B","1C","2C","3C","4C"];
		 If (in_array($code,$list)) {
			 return true;
		 }
		 else 
		 {
			 return false;
		 }
	}
   
	// Function that return Error Messages/Infomation Messages from Code
    function ectt($code)
	{
		switch ($code) 
		{
			case "1A":
				echo "You can't transfer money to yourself";
				break;
			case "2A":
				echo "The recipient account does not exist, please check again.";
				break;
			case "3A":
				echo "There are not enough funds in your account to transfer funds!";
				break;
			case "4A":
				echo "The remittance was successful!";
				break;
				
			case "1B":
			    echo "Your email does not match any account!";
				break;
			case "2B":
			    echo "Your password is incorrect!";
				break;
			case "3B":
			    echo "The account has not been verified. Please verify your account. If you have not received this letter, please visit.";
                break;		
			case "4B":
			    echo "The email is already used in another account. Please try again!";
                break;		
            case "5B":
			    echo "We have sent a link with instructions to verify your account to your email. Please check the main mailbox and spam mailbox at the same time.";
                break;		
			case "6B":
			    echo "Please enter the email used to log in to your account and you will receive a password recovery letter.";
                break;	
			case "7B":
			    echo "We have sent a password recovery email to your email address. Please click on the link provided in the email to recover your password.";
                break;	
				
			case "1C":
			    echo "The request was not fulfilled. Please try again later.";
                break;	
			case "2C":
			    echo "The email you entered is incorrect! Please check and try again.";
                break;	
			case "3C":
			    echo "The amount you entered is not a number or a positive number. Please check and try again.";
                break;	
			case "4C":
			    echo "The date, month and year you entered to find the transaction history are incorrect. Please check and try again.";
                break;	

				
		}
	}
}