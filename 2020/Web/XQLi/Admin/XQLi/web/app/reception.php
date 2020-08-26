<?php if(isset($_COOKIE['whoami']) && $_COOKIE['whoami']=='I_ez_administrator_s_assistant') : ?>

<html>
<title>Welcome area</title>
<body>What do you wanna do?</body>
<br><br>
<a href="./url.php"> send a funny video link </a></br>
<a href="./user.php"> create a new user </a><br>
<a href="./flag.php"> Want flag? </a>
    <!-- ./not-an-interesting-file.txt -->
</html>

<?php else : ?>
    <?php header("location:index.php"); ?>
<?php endif; ?>


