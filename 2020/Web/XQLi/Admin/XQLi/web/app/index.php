
<html>
	<head><title>Security Door</title></head>
    <form name="query" method="POST">
    <br>select  <input type="text" name="end">
    <input type="submit"  name="sub" value="submit">
    </form>
    <!-- ./plan.txt -->
</html>



<?php

include ("indexhelper.php");

$query=$_POST['end'];


$filters="concat|information|schema|hex|md5|load|into|outfile|encrypt|compress|code|right|left|cast|procedure|make|mid|substr|php|inject|collation|coalesce|0x|";
$filters.="0b|eat|trim|substr|cast|insert|delete|import|group|quote|not|union|replace|or|like|insert|inno|-|\.|#|\/|_|alias|wer|sleep|bench|pad|inkypinky|inky";

if(isset($query)){
    if(preg_match("/$filters/i", $query) || substr_count($query, "from")<1 || substr_count($query, "(")>1 || substr_count($query,"\\")>0 ||substr_count($query, '"')>0 || substr_count($query, "'")>2){
        exit('hack found');
    }
}

if(isset($query)){
    $sql="select ".$query;
    if (!$conn -> query($sql)){
        exit("");
    }
    if($sql['id']){
        $result = $conn->query($sql);
        $row = $result->fetch_assoc();
        if($row['id']==="inkypinky"){
            echo "Successful";
            setcookie("whoami", "I_ez_administrator_s_assistant", 0, "/");
            header("location:reception.php");
        }
        else{
            echo "false";
        }
    }
}


 
?>
