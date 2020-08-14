<?php

$headerCSP = "Content-Security-Policy: default-src 'self'; script-src 'self' 'unsafe-inline' www.google.com www.gstatic.com; frame-src 'self' www.google.com;";
header($headerCSP);

// session values
$session = new mysqli("db", "root", "star7ricks", "session");
if ($session -> connect_errno) {
    echo "Failed to connect to MySQL: " . $mysqi -> connect_error;
    exit();
}


// URL to visit
$urlV = new mysqli("db", "root", "star7ricks", "URL");
if ($urlV -> connect_errno) {
    echo "Failed to connect to MySQL: " . $mysqi -> connect_error;
    exit();
}

