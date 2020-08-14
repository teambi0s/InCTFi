<?php if(isset($_COOKIE['whoami']) && $_COOKIE['whoami']=='I_ez_administrator_s_assistant') : ?>


<?php
include("config.php");

echo '
<html>
    <head><title>Corporate</title></head>
    <h2>Enter a userid of the following type :  [A-Z0-9]{4}-[A-Z0-9]{5}-[A-Z0-9]{4}</h2>
    <h6>Warning: Your ID will be deleted once used.<br>PS: This is also accessible only by admin</h6>
    <form name="session" method="GET">
    <br>cookie value for user  <input type="text" name="session">
    <input type="submit"  name="sub" value="submit">
    </form>
</html>

';

function isAdmin() {
    if(gethostbyname("web")===gethostbyname($_SERVER['HTTP_HOST'])){
        return true;
     }
}


$filters = "script";

if (isset($_GET['sub'])){
    $cook=$_GET['session'];

    if(preg_match("/$filters/i", $cook) || substr_count($cook, "<")>1){
        die ("   hecc word found   ");
    } 
    echo "value you entered: $cook";
    if(isadmin()){
        if (preg_match('/^\{?[A-Z0-9]{4}-[A-Z0-9]{5}-[A-Z0-9]{4}\}?$/i', $cook)){
        
            $sessq="select * from coookie where value = ('".$cook."');";
        
            $damn = $session->query($sessq);
            
            if(mysqli_num_rows($damn)>=1){
                echo "inctf{p3op13_persons_c7f_pe0p13_9986000}";
                $del="delete from coookie where value = '".$cook."'";
                $leet = $session-> query($del);
            };
        }
        else{
            echo("<br><br>Not in format");
        }
    }
}

?>

<?php else : ?>
    <?php header("location:index.php"); ?>
<?php endif; ?>


