package main

import (
	"database/sql"
	"log"
	"strconv"
	"strings"
	"time"

	_ "github.com/go-sql-driver/mysql"
)

var db *sql.DB
var err error

/*
	USER TABLE STUFF HERE
*/
func createUserTable() bool {
	query := `CREATE TABLE IF NOT EXISTS users (user_id INT AUTO_INCREMENT,username VARCHAR(255) NOT NULL UNIQUE,password VARCHAR(255) NOT NULL,created_at DATETIME,PRIMARY KEY (user_id));`

	err := db.Ping()
	if err != nil {
		log.Fatal(err)
		return true
	}

	_, err = db.Exec(query)
	if err != nil {
		log.Fatal(err)
		return true
	}
	return false
}

func insertUser(username string, password string) (bool, string) {
	createdAt := time.Now()
	_, err := db.Exec(`INSERT INTO users (username, password, created_at) VALUES (?,?,?);`, username, password, createdAt)
	if err != nil {
		return true, err.Error()
	}
	return false, "User added"
}

func checkUser(username string, password string) (bool, string) {
	var dbpassword string
	query := "SELECT password FROM users WHERE username = ?"
	if err := db.QueryRow(query, username).Scan(&dbpassword); err != nil {
		return true, "User Not Found"
	}
	if strings.Compare(dbpassword, password) == 0 {
		return false, "User Found"
	}
	return true, "Password Incorrect"
}

/*
	NOTES TABLE STUFF HERE
*/
func createNotesTable() bool {
	query := `CREATE TABLE IF NOT EXISTS notes (note_id INT AUTO_INCREMENT, note VARCHAR(2000) NOT NULL, username VARCHAR(255) NOT NULL,created_at DATETIME, reported VARCHAR(255), PRIMARY KEY (note_id), FOREIGN KEY (username) REFERENCES users(username));`

	err := db.Ping()
	if err != nil {
		log.Fatal(err)
		return true
	}

	_, err = db.Exec(query)
	if err != nil {
		log.Fatal(err)
		return true
	}
	return false
}

func insertNote(username string, note string) (bool, string) {
	createdAt := time.Now()
	result, err := db.Exec(`INSERT INTO notes (username, note, created_at, reported) VALUES (?,?,?,?);`, username, note, createdAt, "N")
	if err != nil {
		return true, err.Error()
	}
	id, err := result.LastInsertId()
	return false, "Note Id: " + strconv.FormatInt(id, 10)
}

func updateNote(note_id string) (bool, string) {
	query := `UPDATE notes SET reported = "Y" WHERE note_id = ?`
	_, err := db.Exec(query, note_id)
	if err != nil {
		return true, "Note not updated"
	}
	return false, "Note updated"
}

func getNote(note_id string) (bool, string) {
	var dbnote string
	query := "SELECT note from notes where note_id = ?"
	if err := db.QueryRow(query, note_id).Scan(&dbnote); err != nil {
		return true, err.Error()
	}
	return false, dbnote
}

func userNote(noteID string) (bool, string) {
	var dbnote string
	query := "SELECT username from notes where note_id = ?"
	if err := db.QueryRow(query, noteID).Scan(&dbnote); err != nil {
		return true, err.Error()
	}
	return false, dbnote
}

/*
	REPORTS TABLE STUFF HERE
*/
func createReportsTable() bool {
	query := `CREATE TABLE IF NOT EXISTS reports (note_id INT, created_at DATETIME, viewed VARCHAR(255) NOT NULL);`

	err := db.Ping()
	if err != nil {
		log.Fatal(err)
		return true
	}

	_, err = db.Exec(query)
	if err != nil {
		log.Fatal(err)
		return true
	}
	return false
}

func addReport(noteID string) (bool, string) {
	createdAt := time.Now()
	_, err := db.Exec(`INSERT INTO reports (note_id, created_at, viewed) VALUES (?,?,?);`, noteID, createdAt, "False")
	if err != nil {
		return true, err.Error()
	}
	return false, "Report added"
}

func updateReports(noteID string) (bool, string) {
	_, err := db.Exec(`UPDATE reports SET viewed = "True" where note_id = ?`, noteID)
	if err != nil {
		return true, err.Error()
	}
	return false, "Reports set"
}

func getAReport() (bool, string) {
	var dbNote string
	query := "SELECT note_id from reports where viewed = \"False\" limit 1"
	if err := db.QueryRow(query).Scan(&dbNote); err != nil {
		return true, err.Error()
	}
	return false, dbNote
}

func openDBConnection() bool {
	//db, _ = sql.Open("mysql", "r3x:password@(127.0.0.1:3306)/InCTF?parseTime=true")
	db, err = sql.Open("mysql", "sowmya:Chinnu_99@(localhost)/InCTF?parseTime=true")
	err = db.Ping()
	if err != nil {
		log.Fatal(err)
		return true
	}
	return false
}
