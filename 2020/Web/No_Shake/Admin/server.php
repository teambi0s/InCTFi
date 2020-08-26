<?php
echo "220";
echo "<br>";
echo "250";
echo "<br>";
echo "220";
echo "<br>";
$NAME=$_REQUEST['Name'];
$CMD=$_REQUEST['Cmd'];


if(empty($CMD)){
echo "No in No out";
}
elseif ($CMD==="HIDDEN"){
echo sha1($NAME);
}
elseif(strlen($CMD)!==8){
echo "Admin says you are a real vibe killer";
}
elseif (ctype_alnum($CMD)) {
echo "Aye real vibe killer!!";
}
elseif (preg_match('/[\'^£$%&*()}{@#~?><>,|=_+¬-]/', $CMD)){
echo "Aye real vibe killer!";
}


else {
echo "sT4yH0M3";
echo "<br>";
}
?>

