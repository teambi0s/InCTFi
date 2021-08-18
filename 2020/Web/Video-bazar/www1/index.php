<!DOCTYPE html>

<?php

if(isset($_GET['asd'])){
if($_GET['asd']==='THIS_IS_THE_NEW_WAY_TO_DO_STUFF'){
	$a=True;
}else{
	echo 'wroong';
}
}
?>

<head>
<title>VIDEO CONVERTER</title>
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
<style type="text/css">
	/* Dropdown Button */
.dropbtn {
  background-color: #4CAF50;
  color: white;
  padding: 16px;
  font-size: 16px;
  border: none;
}

/* The container <div> - needed to position the dropdown content */
.dropdown {
  position: relative;
  display: inline-block;
}

/* Dropdown Content (Hidden by Default) */
.dropdown-content {
  display: none;
  position: absolute;
  background-color: #f1f1f1;
  min-width: 160px;
  box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
  z-index: 1;
}

/* Links inside the dropdown */
.dropdown-content a {
  color: black;
  padding: 12px 16px;
  text-decoration: none;
  display: block;
}

/* Change color of dropdown links on hover */
.dropdown-content a:hover {background-color: #ddd;}

/* Show the dropdown menu on hover */
.dropdown:hover .dropdown-content {display: block;}

/* Change the background color of the dropdown button when the dropdown content is shown */
.dropdown:hover .dropbtn {background-color: #3e8e41;}
</style>
</head>

<body>
<?php
if($a){
?>
	<!--
	<form action="upload_file.php" method="post" enctype="multipart/form-data">
		<label for="file"><span>Filename:</span></label>
		<input type="file" name="file" id="file" /> 
		<br />
		<input type="submit" name="submit" value="Submit" />
	

<form action="upload_file.php" method="post" enctype="multipart/form-data">
      <span>Choose files</span>
      <input type="file" name="file" id="file">
  <br>
  Convert to what format
<select name="Color">
<option value="mp4">mp4</option>
<option value="avi">avi</option>
<option value="wma">wma</option>
<option value="gif">gif</option>
</select>
<br>
<input type="submit" name="submit">
</form>
-->
<center>
	<h1>WELCOME TO MY AWESOME VIDEO CONVERTER</h1>
	<br>
</center>
<form action="upload_file.php" method="post" enctype="multipart/form-data">
  <div class="form-group">
    <label for="exampleInputEmail1"><span>Choose files</span></label>
    <input type="file" name="file" id="file" class="form-control" aria-describedby="emailHelp">
    <small id="emailHelp" class="form-text text-muted">Files are Cool</small>
  </div>
  <div class="form-group">
    <label for="exampleInputPassword1">
  <select name="Color">
<option value="mp4">mp4</option>
<option value="avi">avi</option>
<option value="wma">wma</option>
<option value="gif">gif</option>
</select>
    </label>
  </div>
  <input name="submit" type="submit" class="btn btn-primary">Submit</button>
</form>
<?php
}else{
?>
<form action='.' method='GET'>
ENTER THE SUPER SECRET KEY:<input type='text' name='asd'>
</form>
hello
<?php
}
?>
</body>
</html>
