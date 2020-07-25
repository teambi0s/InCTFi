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
  unset($blacklist);
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

