<?php

$input = $_GET['input'];

function check(){
  global $input;
  foreach (get_defined_functions()['internal'] as $blacklisted) {
      if (preg_match ('/' . $blacklisted . '/im', $input)) {
          echo "Your input is blacklisted" . "<br>";
          return true;
          break;
      }
  }
  $blacklist = "exit|die|eval|\[|\]|\\\|\*|`|-|\+|~|\{|\}|\"|\'";
  if(preg_match("/$blacklist/i", $input)){
    echo "Do you really you need that?" . "<br>";
    return true;
  }

  unset($blacklist);
  if(strlen($input)>100){  #That is random no. I took ;)
    echo "This is getting really large input..." . "<br>";
    return true;
  }
  return false;
}

$thisfille=$_GET['thisfile'];

if(is_file($thisfille)){
  echo "You can't use inner file" . "<br>";
}
else{
  if(file_exists($thisfille)){
    if(check()){
      echo "Naaah" . "<br>";
    }else{
      eval($input);
    }
  }else{
    echo "File doesn't exist" . "<br>";
  }

}

function iterate($ass){
	foreach($ass as $hole){
		echo "AssHole";
	}
}

highlight_file(__FILE__);
?>
