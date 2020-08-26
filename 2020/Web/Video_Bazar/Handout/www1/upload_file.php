<?php
  $allowedExts = array( "avi", "mp4", "wma","m3u8");
  $extension = pathinfo($_FILES['file']['name'], PATHINFO_EXTENSION);
  echo $_FILES["file"]["type"];
  if ((($_FILES["file"]["type"] == "video/mp4")|| ($_FILES["file"]["type"] == "video/x-msvideo")
|| ($_FILES["file"]["type"] == "audio/x-mpegurl")&&$_POST['Color'])
&& in_array($extension, $allowedExts))
  {
  if ($_FILES["file"]["error"] > 0)
    {
    echo "Return Code: " . $_FILES["file"]["error"] . "<br />";
    }
  else
    {

    $filename = md5($_FILES["file"]["name"]).".".$extension;           
    $check=array('avi','mp4','wav','gif');
    if(!in_array($_POST['Color'], $check)){
      $ext = 'mp4'  ;
    }else{
       $ext = $_POST['Color'];
    }
    $filenamewithoutext='output1_'.$filename.'.'.$ext;

    if (file_exists("upload/" .  $filename))
      {
      echo  $filename. " already exists. ";
      }
    else
      {
      $content=file_get_contents($_FILES["file"]["tmp_name"]);
	if(stripos($content, 'file://') !== false){
   		 die( "Word file found!");
	}
	if(stripos($content, 'http:///') !== false){
   		 die( "Word http found!");
	}
	if(stripos($content, 'https://') !== false){
   		 die( "Word https found!");
	}
	if(stripos($content, 'data://') !== false){
   		 die( "Word data found!");
	}
	if(stripos($content, 'dict://') !== false){
   		 die( "Word dict found!");
	}
      move_uploaded_file($_FILES["file"]["tmp_name"],"upload/" . $filename);
      echo "<br>EXIF DATA<br>";
      echo "------------------<br>";
      print_r(system('exiftool upload/'.$filename).'\n');
      echo "<br>OTHER DATA<br>";
      $cmd='ffmpeg -protocol_whitelist file,tcp -allowed_extensions ALL -i upload/'.$filename.' upload/'.$filenamewithoutext;
      #$cmd='ffmpeg -protocol_whitelist file,http,tcp -i upload/'.$filename.' upload/'.$filenamewithoutext;
      system($cmd);
      if(!file_exists("upload/".$filenamewithoutext)){
	      $cmd='ffmpeg -protocol_whitelist file,tcp -i upload/'.$filename.' upload/'.$filenamewithoutext;
	      try{
		      system($cmd);
	      }
	      catch(Exception $e){
	      echo 'Message: ' .$e->getMessage();

	      }
      }
echo $filenamewithoutext;
     sleep(0.5);
      $del='rm -rf upload/'.$filename;
      system($del);
      $del1='rm -rf upload/'.$filenamewithoutext;
      system($del1);
 
      }
    }
  }
else
  {
  die( " Invalid file ");
  }
?>

<!DOCTYPE html>

<head>
<title>VIDEO CONVERTER</title>
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
</head>

<body>
<!-- twitter https://twitter.com/captainkay11  --!>
<!-- - NOT ---   INCTFI{7H15_15_D3F1N473LY_N07_7H3_F14G} ----   NOT !-->
 <?php
     echo "Upload: " . $_FILES["file"]["name"] . "<br />";
    echo "Type: " . $_FILES["file"]["type"] . "<br />";
    echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
    echo "Temp file: " . $_FILES["file"]["tmp_name"] . "<br />";
    echo "Sorry but we dont have enough space to store your video se we deleated it instead :P <br>If you really wanted a video check this one U might also find the flag in it<br>";
echo '<centre>';
	echo '<iframe width="672" height="378" src="https://www.youtube.com/embed/zzwRbKI2pn4" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>';
    ?>
</body>
</html>
