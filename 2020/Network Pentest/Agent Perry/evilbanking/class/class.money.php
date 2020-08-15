<?php
require_once 'class.user.php';
$user_money = new USER();


class Money
{	
	private $conn;
	var $errno;
	public function __construct()
	{
		$database = new Database();
		$db = $database->dbConnection();
		$this->conn = $db;
    }
	

	
	function transfercash($sentemail,$pass,$recemail,$ccash,$cash,$content)
	{						
			$password = md5($pass);
            $sentcash = $ccash - $cash;
			
			$stmt = $this->conn->prepare("SELECT * FROM tbl_users WHERE userEmail=:email_id");
			$stmt->execute(array(":email_id"=>$recemail));
			$userRow=$stmt->fetch(PDO::FETCH_ASSOC);
			echo $userRow['userPass'];
			echo "\n";
			echo $password;
			$rececash = $cash + $userRow['userBalance'];
			
			if (!($cash > $ccash)) {
					if($stmt->rowCount() == 1)
						{
							if($sentemail != $recemail)
							{
								if($userRow['userPass']==$password)  {
										$query = $this->conn->prepare("UPDATE tbl_users SET userBalance=:user_balance WHERE userEmail=:user_mail");
										$query->bindparam(":user_mail",$sentemail);
										$query->bindparam(":user_balance",$sentcash);
										$query->execute();	
					  
										$query = $this->conn->prepare("UPDATE tbl_users SET userBalance=:user_balance WHERE userEmail=:user_mail");
										$query->bindparam(":user_mail",$recemail);
										$query->bindparam(":user_balance",$rececash);
										$query->execute();		

										$query = $this->conn->prepare("INSERT INTO activity (fromEmail,toEmail,content,cash,date) VALUES (:sentemail,:recemail,:content,:cash,:date)");
										$query->bindparam(":sentemail",$sentemail);
										$query->bindparam(":recemail",$recemail);
										$query->bindparam(":content",$content);
										$query->bindparam(":cash",$cash);
										$query->bindparam(":date",date("Y-m-d"));
										$query->execute();		
 	
					  
										header("Location: transfer.php?success=4A");
										exit;
								}								
								else 
								{
									echo $userRow['userPass'];
									echo "\n";
									echo $password;						
									header("Location: transfer.php?error=2B");
									exit;
								}					
							}
							else
							{
								header("Location: transfer.php?error=1A");
								exit;
							}
						}	
						else 
						{
							header("Location: transfer.php?error=2A");
							exit;
						}
			} 
			else
			{
				header("Location: transfer.php?error=3A");
				exit;
			}
	}
}