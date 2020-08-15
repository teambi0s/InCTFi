<?php
session_start();
require '../config/dbconfig.php';
require_once '../class/class.user.php';
require_once '../class/class.error.php';
$user_activity = new USER();
$eror_activity = new ErrorRep();
if(!$user_activity->is_logged_in())
{
	$user_activity->redirect('../login.php');
}

$stmt = $user_activity->runQuery("SELECT * FROM tbl_users WHERE userID=:uid");
$stmt->execute(array(":uid"=>$_SESSION['userSession']));
$row = $stmt->fetch(PDO::FETCH_ASSOC);

$dateFrom = date("d/m/Y");
$dateTo = date("d/m/Y");

if(isset($_POST['date-search'])) 
{
   $dateFrom = addslashes($_POST['timeCheckIn']);
   $dateTo = addslashes($_POST['timeCheckOut']);
   if ((checkdate((int)substr($dateFrom,4,2),(int)substr($dateFrom,1,2),(int)substr($dateFrom,7,4))) AND (checkdate((int)substr($dateTo,4,2),(int)substr($dateTo,1,2),(int)substr($dateTo,7,4)))) 
	   if ((strlen($dateTo)==10) AND (strlen($dateFrom)==10))
			{	
				
			}
   else
   {
	   header("Location: activity.php?error=4C");
	   exit;
   }
}
?>

<!DOCTYPE html>
<html class="no-js">
    
    <head>
        <title>Edit personal information-PiggyBank</title>
        <?php include("../template/header.php") ?>

    </head>
    
    <body>
	 <?php include("../template/menu_ac.php") ?>
	 </br></br>
       <div class="container">
	  <?php
        if(isset($_GET['error']))
			if ($eror_activity->exist($_GET['error'])) 
				{
					?>
						<div class='alert alert-warning'>
						<button class='close' data-dismiss='alert'>&times;</button>
						<strong><?php $eror_activity->ectt($_GET['error']); ?></strong> 
						</div>
					<?php
				}
					?>
	   <?php
        if(isset($_GET['success']))
			if ($eror_activity->exist($_GET['success'])) 
				{
					?>
						<div class='alert alert-success'>
						<button class='close' data-dismiss='success'>&times;</button>
						<strong><?php $eror_activity->ectt($_GET['success']); ?></strong> 
						</div>
					<?php
				}
					?>      
  <h2>Personal information</h2>
       <form class="form-signin" method="post">
	   <?php
        if(isset($_GET['error']))
		{
			?>
            <div class='alert alert-warning'>
				<button class='close' data-dismiss='alert'>&times;</button>
				<strong><?php $reg_error->ectt($_GET['error']); ?></strong> 
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
				<strong><?php $reg_error->ectt($_GET['success']); ?></strong> 
			</div>
            <?php
		}
		?>
		 <div class="form-group">
			    <label>First name and last name</label>
                <input type="text" class="form-control" value="<?php echo $row['userName']; ?>" name="uname" />
		</div>
		
		<div class="form-group">
			    <label>Your mail</label>
                <input type="email" class="form-control" value="<?php echo $row['userEmail']; ?>" name="email" disabled />
		</div>
		
		<div class="form-group">
			    <label>PIN code</label>
                <input type="email" class="form-control" placeholder="constant" name="email" />
		</div>
		
		<div class="form-group">
			    <label>current password</label>
                <input type="password" class="form-control" name="ucpass" required />
		</div>
		
		<div class="form-group">
			    <label>new password</label>
                <input type="password" class="form-control" name="unpass" required />
		</div>
		
		<div class="form-group">
			    <label>Confirm the new password</label>
                <input type="password" class="form-control" name="uncpass" required />
		</div>
        <button class="btn btn-large btn-primary" type="submit" name="submit">Save</button>
      </form>
  </br>


	   </div>
       <?php include("../template/footer_ac.php") ?> 
       <?php include("../template/misc.php") ?>

    </body>

</html>