<html>
<head>
	<title>S3cur3 Bank</title>
</head>
</html>

<?php

$page = $_SERVER['HTTP_REFERER'];

$a =  parse_url($page, PHP_URL_QUERY);
parse_str($a, $a);

$id =  $a['id'];

if(!preg_match("/^[a-z0-9]*$/", $id))
{
        die("Invalid characters detected: Only lowercase alphanumeric allowed");
}

$host = 'localhost';
$dbuser = 'root';
$dbpass = 'toor';
$dbname = 'inctf_chall';

$conn = mysqli_connect($host,$dbuser,$dbpass,$dbname);
if (!$conn)
{
    die("<center>Connection failed</center>");
}

$query = 'update records set id=NULL where id="' . $id . '"';

$result = mysqli_query($conn,$query);
if(!$result)
{
	die("Unable to properly logout");
}

die("You have successfully logged out");

?>
