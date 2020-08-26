<?php

if(isset($_COOKIE['whoami'])) {
    if($_COOKIE['whoami']=='I_ez_administrator_s_assistant'){
        header("location:reception.php");
    }
}


$conn = new mysqli("db","root","star7ricks","inctf");
if ($conn -> connect_errno) {
    echo "alert('problem')";
    echo "Failed to connect to MySQL: " . $mysqi -> connect_errno;
    exit();
}
