<?php
include("./config.php");

$db_connection = pg_connect($host. $dbname .$user. $pass);
if (!$db_connection) {
    die("Connection failed");
}


$name = $_GET['name'];
$column = $_GET['column'];

$blacklist  = "adm|min|\'|substr|mid|concat|chr|ord|ascii|left|right|for| |from|where|having|trim|pos|";
$blacklist .= "insert|usern|ame|-|\/|go_to|or|and|#|\.|>|<|~|!|like|between|reg|rep|load|file|glob|cast|out|0b|\*|pg|con|%|to|";
$blacklist .= "rev|0x|limit|decode|conv|hex|in|from|\^|union|select|sleep|if|coalesce|max|proc|exp|group|rand|floor";

if (preg_match("/$blacklist/i", $name)){
  die("Try Hard");
}

if (preg_match("/$blacklist/i", $column)){
  die("Try Hard");
}

$query = "select " . $column . " from inctf2020 where username = " . $name ;

$ret = pg_query($db_connection, $query);

if($ret){
while($row = pg_fetch_array($ret)){
if($row['username']=="admin"){
      header("Location:{$row['go_to']}");
}
  else{
      echo "<h4>You are not admin " . "</h4>";
  }

}
}else{
echo "<h4>Having a query problem" . "</h4><br>";
}

highlight_file(__FILE__);
?>

