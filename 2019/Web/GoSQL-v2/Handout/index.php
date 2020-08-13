<?php
include("./config.php");
$conn = mysqli_connect($host,$dbuser,$dbpass,$dbname);
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

$name = $_GET['name'];

$blacklist  = "pad|ad|min|\"|substr|mid|concat|char|ascii|left|right|for| |from|where|having|";
$blacklist .= "insert|username|\/|go_to|\||or|and|\\\|=|#|\.|\_|>|like|between|reg|&|load|file|glob|cast|out|0b|";
$blacklist .= "rev|0x|limit|decode|conv|hex|in|from|innodb|\^|union|benchmark|sleep|if|case|coalesce|max|strcmp|proc|exp|group|rand|floor|pow";

if (preg_match("/$blacklist/i", $name)){
  die("Try Hard");
}

$query="select * from inctf2018_chall_2 where username='" . $name . "'";
echo "<h4>query: " . $query . " </h4>";
$result=mysqli_query($conn,$query);
if($result){
  $row=mysqli_fetch_array($result);
  if($row['username']=="admin"){
      header("Location:{$row['go_to']}");
}
  else{
      echo "<h4>You are not admin " . "</h4>";
  }
}
else{
  echo "<h4>Having a query problem" . "</h4><br>";
}
highlight_file(__FILE__);
?>
