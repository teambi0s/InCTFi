# Setup

Things needed on the server to run the program
## Main
TODO: mention how you setup Go

## Go packages

- `go get -u github.com/go-sql-driver/mysql`
- `go get -u github.com/gorilla/mux`

## MySQL
on command line
- `sudo apt install mysql-server`
- `sudo mysql_secure_installation utility`
- `sudo mysql -u root -p`

In the mysql prompt
- `GRANT ALL on *.* to 'username'@'localhost' identified by 'password';`
- `flush privileges;`
- `create database InCTF`

replace the username, password in `db.go`