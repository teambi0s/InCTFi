<?php
$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

$blacklist = "import|os|class|subclasses|mro|request|args|eval|if|for|\%|subprocess|file|open|popen|builtins|\+|compile|execfile|from_pyfile|config|local|\`|\||\&|\;|\{|\}";

if(!$_FILES["fileToUpload"]["name"])
{
	die("PLEASE UPLOAD SOMETHING");
}

// Check if image file is a actual image or fake image
if(isset($_POST["submit"])) {
    $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
    if($check !== false) {
        echo "File is an image - " . $check["mime"] . "<br>";
        $uploadOk = 1;
    } else {
        echo "File is not an image." . "<br>";
        $uploadOk = 0;
    }
}

// Check file size
if ($_FILES["fileToUpload"]["size"] > 500000) {
    echo "Sorry, your file is too large." . "<br>";
    $uploadOk = 0;
}

// Allow certain file formats
if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
&& $imageFileType != "gif" ) {
    echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed." . "<br>";
    $uploadOk = 0;
}

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded." . "<br>";
    exit();
}
// if everything is ok, try to upload file

if (preg_match("/$blacklist/i", $_FILES["fileToUpload"]["name"])){
    echo "<br>Filename: ".$_FILES["fileToUpload"]["name"]."<br><br>";
    die("I think its called blacklisting...!");
}

echo "The file: ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded." . "<br>";
echo "File: " . $_FILES["fileToUpload"]["name"] . "<br>";
echo "Size: " . $_FILES["fileToUpload"]["size"] . "<br>";
echo "Type: " . $_FILES["fileToUpload"]["type"] . "<br>";
echo "<br><br><br>";
echo $name = urldecode($_FILES["fileToUpload"]["name"]);
echo "<br><br><br>";
echo shell_exec("python -c \"" . $name . "\" 2>&1");

?>
