<?php
error_reporting(0);
include('flag.php');
$message = "<img src='cat.jpg' height=400><!-- is_debug -->";

if (isset($_GET['is_debug']))
	{
	highlight_file(__FILE__) and die();
	}
  else
	{
	$qs = $_SERVER['QUERY_STRING'];
	if(!(substr_count($qs, '_') > 0) && !(substr_count($qs, '%')> 1))
		{
			$cmd = $_GET['c_m_d'];
			if(!preg_match('/[a-z0-9]/is', $cmd)){
				system("/sandboxed_bin/".$cmd);
			}else{
				echo $message;
				die();
			}
		}
	echo $message;
		die();
	}
?>

