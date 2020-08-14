<?php
$start="key?"; 
$flag0="if (isset(\$_GET['abc'])){
        if (!strcasecmp (\$_GET['abc'], \$flag1))
		echo \$flag1;
		else
        echo 'Aye real vibe killer';}";
$flag1="if (isset (\$_GET['def'])){  \$def = \$_GET['def'];
                                    \$obj = unserialize (\$def);
                                    \$obj->flag = \$flag2;
                                    if (hash_equals (\$obj->xyz, \$obj->flag))
				     echo \$flag2;
				         else
                                            echo 'Aye real vibe killere!';}";
$flag2="  if(isset(\$_GET['ghi'])){   class Dogs {
                                        public \$obj;
                                        public function __construct(){
                                        \$this-> obj = Null;
                                        }
                                        public function __wakeup(){
                                        \$this-> end();
                                        }
                                        public function end(){
                                        \$this-> obj-> close();
                                        }
                                        }
                                        class Cats{
                                        public function close(){
                                        system(\$this-> cmd);
                                        }
                                        }
                                        \$data= unserialize(\$_GET['ghi']);
                                     }
                                     else
                                             echo 'Aye real vibe killerr!';";


echo $start;
if($_GET['key']=="sT4yH0M3"){
echo $flag0;
echo "<br>";
echo "<br>";
if (isset($_GET['abc'])){
	if (!strcasecmp ($_GET['abc'], $flag1)){
		echo $flag1;
		echo "<br>";
		echo "<br>";
		if (isset ($_GET['def'])){
			            $def = $_GET['def'];
                                    $obj = unserialize ($def);
                                    $obj->flag = $flag2;
                                    if (hash_equals ($obj->xyz, $obj->flag))
				    {   echo $flag2;
				    echo "<br>";
				    echo "<br>";

				     if(isset($_GET['ghi'])){   class Dogs {
          				public $obj;
        				public function __construct(){
        				$this-> obj = Null;
        				}
        				public function __wakeup(){
    					$this-> end();
        				}
        				public function end(){
        				$this-> obj-> close();
        				}
					}
					class Cats{
       					public function close(){
        				system($this-> cmd);
        				}
					}
					$data= unserialize($_GET['ghi']);
				     }       
				     else
					     echo "Aye real vibe killerr!";
		
				    }

                 		    else
                                            echo "Aye real vibe killere!";
		  }


}
else
        echo 'Aye real vibe killer';
}}
$ffflllaaaggg="inctf{Rc3_n_d0wngr4d35_d0n7_g0_W3Ll:}"
?>
