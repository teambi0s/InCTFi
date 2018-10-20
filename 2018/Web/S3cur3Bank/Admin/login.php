<html>
<head>
	<title>S3cur3 Bank</title>
</head>
</html>
<?php

$host = 'localhost';
$dbuser = 'root';
$dbpass = 'toor';
$dbname = 'inctf_chall';

$user = $_POST['user'];

$pass = $_POST['pass'];

if(!preg_match("/^[a-zA-Z0-9]*$/", $user))
{
        die("Invalid characters detected: Only alphanumeric allowed");
}

if(!preg_match("/^[a-zA-Z0-9]*$/", $pass))
{
        die("Invalid characters detected: Only alphanumeric allowed");
}

$conn = mysqli_connect($host, $dbuser, $dbpass, $dbname);

if (!$conn)
{
    die("Connection failed");
}

$query = "select * from records where username = '$user' and password = '$pass'";

$result = mysqli_query($conn,$query);

if($result)
{
        $row = mysqli_fetch_array($result);
        if(count($row['username'])==1)
        {
		$id = 'q1wer1t14yu6i7op' . $user . 'qw41er6ty81ui91o0p';
		$id = hash('md5',$id);
		$que = "update records set id='" . $id . "' where username = '$user'";
		$res = mysqli_query($conn, $que);
		if($res)
		{
			header("location:./bank.php?id=" . $id);
		}
		else
		{
			die("Unable to login");
		}
        }
        else
        {
                die("Invalid Credentials");
        }
}
else
{
        die("Internal Error: Please ask an admin");
}
?> 
