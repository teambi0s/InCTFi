<?php

    $con=mysqli_connect('localhost','chaluser','Abcd@123','challenge');
    if(!$con){
        echo 'Connection error :' .mysqli_connect_error();
    }
?>
