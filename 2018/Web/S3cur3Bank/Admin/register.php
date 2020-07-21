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

$query = "insert into records(username, password, A, B) values('$user', '$pass', 1000, 1000)";

$result = mysqli_query($conn,$query);

if($result)
{
	die("User created");	
}
else
{
        die("Username already Exists");
}

?>
