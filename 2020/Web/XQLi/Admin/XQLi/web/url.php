<?php if(isset($_COOKIE['whoami']) && $_COOKIE['whoami']=='I_ez_administrator_s_assistant') : ?>

<?php include("config.php"); ?>

<html>
<head><title>Conference Room?</title></head>
    <form name="URL" method="POST">
    <br>url  <input type="text" name="url">
    <input type="submit"  name="sub" value="submit">
    </form>
    <p5>I would like to let you know that the max length is 35</p5><br><br>
</html>

<?php
if (isset($_POST['sub'])){
    $cook=$_POST['url'];
    $url = filter_var($cook, FILTER_SANITIZE_URL);

    $filter = "127.0.0.1|assistant|index|user|config|url|localhost|flag|inctf";

    if (filter_var($url, FILTER_VALIDATE_URL) === FALSE) {
        die('Not a valid URL');
    }

    if(preg_match("/$filter/i", $url)){
        die('I know there are no funny videos in my own domain');
    }

    if(strlen($url)>35){
	die('really?');
    }

    $sessq="insert into www values ('".$url."');";
    $damn = $urlV->query($sessq);
    echo " <br><br><br>The admin will take a look at the link you sent ";
}
?>

<?php else : ?>
    <?php header("location:index.php"); ?>
<?php endif; ?>