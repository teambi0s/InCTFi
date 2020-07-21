<?php

if(!isset($_GET['id']))
{
	die("You are not logged in");
}

$id = $_GET['id'];

if(!preg_match("/^[a-z0-9]*$/", $id))
{
        die("Invalid characters detected: Only lowercase alphanumeric allowed");
}

$host = 'localhost';
$dbuser = 'root';
$dbpass = 'toor';
$dbname = 'inctf_chall';

$conn = mysqli_connect($host,$dbuser,$dbpass,$dbname);
if (!$conn)
{
    die("<center>Connection failed</center>");
}

$query = 'select * from records where id="' . $id . '"';
$result = mysqli_query($conn,$query);
if($result)
{
        $row = mysqli_fetch_array($result);
        if(count($row['id'])==1)
        {
                $username = $row['username'];
        }
        else
        {
                die("You are not logged in");
        }
}

?>
<html>
<head>
	<title>S3cur3 Bank</title>
	<link rel="stylesheet" href="main.css">
</head>

<body>
<br>

<h1><center>S3cur3 Bank</center></h1>

<h3 style="text-align:right; padding-right:2%">User: <?php echo $username; ?></h3>
<h4 style="text-align:right; padding-right:2%"><a href="logout.php">Logout</a></h4>

<br>
<div style="padding-left:5%; float:left; font-size: 200%;">
	Bank A
</div>

<div style="padding-right:5%; float:right; font-size: 200%;">
	Bank B
</div>

<br><br>
<div class="login-wrap" style="margin-left:5%; min-height:400px; max-width:400px; float: left">	
	<div class="login-html" style="color: white;">
		Account Balance: 
		<?php
			$balance = getBalance('A', $id);
			echo $balance . " credits<br><br>";
		?>
		<form method="post">	
			<input type="text" name="transfer" placeholder=" Amount to tranfer to bank B ">
			<br><br>
			<input type="submit" name="account" value="Transfer to B">
		</form>
		<br>
                Buy flag from this bank?<br><br>
                <form method="post">
                        <input type="submit" name="buy" value="Buy from A">     
                </form>
	</div>

</div>

<div class="login-wrap" style="margin-right:5%; min-height:400px; max-width:400px; float: right">
        <div class="login-html" style="color:white;">
	Account Balance: 
                <?php
                        $balance = getBalance('B', $id);
                        echo $balance . " credits<br><br>";
                ?>
		<form method="post">
                	<input type="text" name="transfer" placeholder=" Amount to tranfer to bank A ">
                	<br><br>
                	<input type="submit" name="account" value="Transfer to A">
		</form>
		<br>	
		Buy flag from this bank?<br><br>
		<form method="post">
			<input type="submit" name="buy" value="Buy from B">
		</form>	
        </div>
</div>

<?php

function getBalance($account, $id)
{
        $host = 'localhost';
        $dbuser = 'root';
        $dbpass = 'toor';
        $dbname = 'inctf_chall';
        $conn = mysqli_connect($host,$dbuser,$dbpass,$dbname);
        if (!$conn)
        {
            die("<center>Connection failed</center>");
        }
        $query = 'select ' . $account .' from records where id ="' . $id . '"';
        $result = mysqli_query($conn,$query);
        if($result)
        {
                $row = mysqli_fetch_array($result);
                if(count($row)==2)
                {
                        return $row[$account];
                }
                else
                {
                        die("<center>Error in retreiving balance</center>");
                }
        }
        else
        {
                die("<center>ERROR</center>");
        }
}

function setBalance($account, $amount, $id)
{
        $host = 'localhost';
        $dbuser = 'root';
        $dbpass = 'toor';
        $dbname = 'inctf_chall';
        $conn = mysqli_connect($host,$dbuser,$dbpass,$dbname);
        if (!$conn)
        {
            die("<center>Connection failed</center>");
        }
        $query = 'update records set ' . $account . '=' . $amount . ' where id ="' . $id . '"';
        $result = mysqli_query($conn,$query);
        if($result)
        {
                echo "<br><center>Update Successful</center>";
        }
        else
        {
                die("<center>ERROR</center>");
        }
}

function addBalance($account, $amount, $id)
{
        $host = 'localhost';
        $dbuser = 'root';
        $dbpass = 'toor';
        $dbname = 'inctf_chall';
        $conn = mysqli_connect($host,$dbuser,$dbpass,$dbname);
        if (!$conn)
        {
            die("<center>Connection failed</center>");
        }
        $query = "update records set $account = $account + $amount where id ='" . $id . "'";
        $result = mysqli_query($conn,$query);
        if(!$result)
        {
                die("<center>ERROR</center>");
        }
}

function transfer($account, $to,  $amount, $id)
{
	$balance = getBalance($account, $id);
        if($amount <= $balance)
        {
                $balance = $balance - $amount;
		addBalance($to, $amount, $id);
                setBalance($account, $balance, $id);
                echo "<center><br>You have transfered : $amount from $account to $to</center>";
		$url = $_SERVER['REQUEST_URI'];
		header("Refresh: 1; URL=$url");
        }
        else
        {
                echo "<br><center>Insufficient funds</center>";
        }
}

if(isset($_POST['transfer']) && isset($_POST['account']))
{
	$amount = $_POST['transfer'];
	$account = $_POST['account'];

	if(!preg_match('/^[1-9][0-9]*$/', $amount))
	{
		die("<center>Transfer a valid amount</center>");
	}	

	if($account === 'Transfer to A')
	{
	        $account = 'B';
		$to = 'A';
	}
	else if($account === 'Transfer to B')
	{
	        $account = 'A';
		$to = 'B';
	}
	else
	{
	        die("<center>ERROR</center>");
	}
	
	
	transfer($account, $to, $amount, $id);
}

if(isset($_POST['buy']))
{
	$buy = ($_POST['buy']);
	if($buy==='Buy from A')
	{
		$buy = 'A';
	}
	
	else if($buy==='Buy from B')
	{
		$buy = 'B';
	}
	
	$balance = getBalance($buy, $id);

	if($balance>=5000)
	{
		echo "<br><center>inctf{y0u_r4c3_v3ry_w3ll}</center>";
		addBalance($buy,-5000, $id);
	}
	else
	{
		echo "<br><center>You need 5000 credits to buy the flag...Hack harder</center>";
	}
}

?>

</html>
