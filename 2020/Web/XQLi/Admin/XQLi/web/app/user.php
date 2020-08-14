<?php if(isset($_COOKIE['whoami']) && $_COOKIE['whoami']=='I_ez_administrator_s_assistant') : ?>

<?php include("config.php"); ?>

<html>
	<head><title>HR</title></head>
    <h2>Enter a userid of the following type :  [A-Z0-9]{4}-[A-Z0-9]{5}-[A-Z0-9]{4}</h2>
    <form name="session" method="GET">
    <br>cookie value for user  <input type="text" name="session">
    <input type="submit"  name="sub" value="submit">
    </form>
</html>

<?php

function isAdmin() {
    if(gethostbyname("web")===gethostbyname($_SERVER['HTTP_HOST'])){
        return true;
     }

}

if (isset($_GET['sub'])){
    $cook=$_GET['session'];
    if (preg_match('/^\{?[A-Z0-9]{4}-[A-Z0-9]{5}-[A-Z0-9]{4}\}?$/i', $cook)){
        if(isadmin()===TRUE){
            $sessq="insert into coookie values ('".$cook."');";
            $damn = $session->query($sessq);
            echo "$cook value inserted...";
        }
        else{
            echo ("<script>alert('only admin can create users')</script>");
        }
    }
    else{
        echo "<script>alert('Not in format')</script>";
    }
}

?>

<?php else : ?>
    <?php header("location:index.php"); ?>
<?php endif; ?>


