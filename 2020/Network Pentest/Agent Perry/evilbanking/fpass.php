<?php
session_start();
require 'config/dbconfig.php';
require_once 'class/class.user.php';
require_once 'class/class.error.php';

$user = new USER();
$error = new ErrorRep();

if($user->is_logged_in()!="")
{
	$user->redirect('home.php');
}

if(isset($_POST['btn-submit']))
{
	$email = $_POST['txtemail'];
	if(filter_var($email,FILTER_VALIDATE_EMAIL)) 
	{
	$stmt = $user->runQuery("SELECT userID FROM tbl_users WHERE userEmail=:email LIMIT 1");
	$stmt->execute(array(":email"=>$email));
	$row = $stmt->fetch(PDO::FETCH_ASSOC);	
	if($stmt->rowCount() == 1)
	{
		$id = base64_encode($row['userID']);
		$code = md5(uniqid(rand()));
		
		$stmt = $user->runQuery("UPDATE tbl_users SET tokenCode=:token WHERE userEmail=:email");
		$stmt->execute(array(":token"=>$code,"email"=>$email));
		
		$message= "
				   Hello , $email
				   <br /><br />
				   We got requested to reset your password, if you do this then just click the following link to reset your password, if not just ignore                   this email,
				   <br /><br />
				   Click Following Link To Reset Your Password 
				   <br /><br />
				   <a href='http://localhost/x/resetpass.php?id=$id&code=$code'>click here to reset your password</a>
				   <br /><br />
				   thank you :)
				   ";
		$subject = "Password Reset";
		
		$user->send_mail($email,$message,$subject);
		header("Location: fpass.php?success=7B");
		exit;
	}
	else
	{
		header("Location: fpass.php?success=7B");
		exit;
	}
	}
	else
	{
		header("Location: fpass.php?error=2C");
		exit;
	}
	
	
}
?>

<!DOCTYPE html>
<html>
  <head>
    <title>Forgot Password</title>
    <!-- Bootstrap -->
    <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet" media="screen">
    <link href="bootstrap/css/bootstrap-responsive.min.css" rel="stylesheet" media="screen">
    <link href="assets/styles.css" rel="stylesheet" media="screen">
     <!-- HTML5 shim, for IE6-8 support of HTML5 elements -->
    <!--[if lt IE 9]>
      <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
    <![endif]-->
  </head>
  <body id="login">
    <div class="container">

      <form class="form-signin" method="post">
        <h2 class="form-signin-heading">Forgot Password</h2><hr />
        <?php
        if(isset($_GET['error']))
		{
			?>
            <div class='alert alert-warning'>
				<button class='close' data-dismiss='alert'>&times;</button>
				<strong><?php $error->ectt($_GET['error']); ?></strong> 
			</div>
            <?php
		}
		?>
	<?php
        if(isset($_GET['success']))
		{
			?>
            <div class='alert alert-success'>
				<button class='close' data-dismiss='success'>&times;</button>
				<strong><?php $error->ectt($_GET['success']); ?></strong> 
			</div>
            <?php
		}
		?>
        
        <input type="email" class="input-block-level" placeholder="Email address" name="txtemail" required />
     	<hr />
        <button class="btn btn-danger btn-primary" type="submit" name="btn-submit">Generate new Password</button>
      </form>

    </div> <!-- /container -->
    <?php include("template/misc.php") ?>
  </body>
</html>