import random  
import string  
def Upper_Lower_string(length): # define the function and pass the length as argument  
    # Print the string in Lowercase  
    result = ''.join((random.choice(string.ascii_letters) for x in range(length))) # run loop until the define length  
    return result  
  
    # Print the string in Uppercase  
    result1 = ''.join((random.choice(string.ascii_uppercase) for x in range(length))) # run the loop until the define length  
    return result1