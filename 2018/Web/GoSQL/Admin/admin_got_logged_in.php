<!DOCTYPE html>
<html>
<head><title>SomeTimes hard chall is good</title></head>
<body>
<h2>Welcome Back!!! admin !!!</h2>
<h3>You have one functionality that you can cURL</h3>
<form method=POST>
put url : <input type="text" name="url">
<button type="submit">GO</button>
</form>
</body>
</html>


<?php
$url=$_POST['url'];
if(preg_match("/(dict|ftp|scp|ldap|data|php|ssh|file)/i",$url)){
    die("<h4>Can't you solve, without using it!!!<h4>");
}
$cSession = curl_init();
curl_setopt($cSession,CURLOPT_URL,$url);
curl_setopt($cSession,CURLOPT_RETURNTRANSFER,true);
curl_setopt($cSession,CURLOPT_HEADER, false);
$result=curl_exec($cSession);
curl_close($cSession);
echo $result;
?>
