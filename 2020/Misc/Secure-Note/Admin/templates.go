package main

import (
	"fmt"
	"html/template"
	"io/ioutil"
	"net/http"
	"strings"
)

func staticHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Unimplemented!")
}

func loginpageHandler(w http.ResponseWriter, r *http.Request) {
	renderTemplate(w, "login")
}

func registerpageHandler(w http.ResponseWriter, r *http.Request) {
	renderTemplate(w, "register")
}

func adminRegisterpageHandler(w http.ResponseWriter, r *http.Request) {
	renderTemplate(w, "admin_register")
}

func adminLoginpageHandler(w http.ResponseWriter, r *http.Request) {
	renderTemplate(w, "admin_login")
}

func addNotepageHandler(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		renderTemplate(w, "addNote")
	}
}

func viewNotepageHandler(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		renderTemplate(w, "viewNote")
	}
}

func reportNotepageHandler(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		renderTemplate(w, "reportBug")
	}
}

func renderTemplate(w http.ResponseWriter, tmpl string) {
	t, _ := template.ParseFiles(tmpl + ".html")
	t.Execute(w, nil)
}

func renderDisplayTemplate(w http.ResponseWriter, tmpl string, data MessageData) {
	t := template.Must(template.ParseFiles(tmpl + ".html"))
	t.Execute(w, data)
}

func showResult(w http.ResponseWriter, message string, subtext string) {
	renderDisplayTemplate(w, "result", MessageData{
		Message: message,
		Subtext: subtext,
	})
}

func registerHandler(w http.ResponseWriter, r *http.Request) {
	username := r.FormValue("username")
	password := r.FormValue("password")
	userKey := genKey(username)
	if username != "" && password != "" && username != adminuser { // "admin" --> TBA.
		err, message := insertUser(username, password)
		if err {
			showResult(w, "Unable to register", message)
		} else {
			setLocalSessionCookie(w, r)
			addCookie(w, r, username)
			showResult(w, "Successfully registered", "Your user Key : "+userKey)
		}
	}
}

func adminRegisterHandler(w http.ResponseWriter, r *http.Request) {
	username := r.FormValue("username")
	password := r.FormValue("password")
	userKey := genKey(username)
	if username != "" && password != "" && isAdminReg != true {
		adminuser = username
		adminpassword = password
		isAdminReg = true
		showResult(w, "Successfully registered Admin", "Your user key : "+userKey)
	} else {
		showResult(w, "Unable to register admin!", "Something went wrong")
	}
}

func loginHandler(w http.ResponseWriter, r *http.Request) {
	username := r.FormValue("username")
	password := r.FormValue("password")
	if username != "" && password != "" && username != adminuser {
		err, prompt := checkUser(username, password)
		if !err {
			setLocalSessionCookie(w, r)
			//user_key := genKey(username) not needed here?
			addCookie(w, r, username)
			showResult(w, "Successfully Logged in", prompt)
		} else {
			showResult(w, "Unable to Login", prompt)
		}
	} else {
		showResult(w, "Unable to Login", "Not a proper username or password")
	}
}

func adminLoginHandler(w http.ResponseWriter, r *http.Request) {
	username := r.FormValue("username")
	password := r.FormValue("password")
	if username != "" && password != "" {
		if username == adminuser && password == adminpassword {
			setAdminSessionCookie(w, r)
			addCookie(w, r, username)
			showResult(w, "Successfully Logged in", "Welcome Admin")
		} else {
			showResult(w, "Unable to login", "Improper username or password")
		}
	} else {
		showResult(w, "Unable to Login", "Not a proper username or password provided")
	}
}

func addNoteHandler(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		key := r.FormValue("key")
		note := r.FormValue("note")
		username, userKey, err := decodeSessionCookie(r)
		if err != nil {
			showResult(w, "Unable to deocde session addCookie", err.Error())
		}
		if key != "" && note != "" && userKey == key {
			err, noteID := insertNote(string(username), note)
			if err {
				showResult(w, "Unable to create note", noteID)
			} else {
				showResult(w, "Note Created!", noteID)
			}
		} else {
			showResult(w, "Unable to add note", "Missing fields")
		}
	}
}

func viewNoteHandler(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		noteID := r.FormValue("noteid")
		userkey := r.FormValue("userkey")
		_, key, err := decodeSessionCookie(r)
		if err != nil {
			showResult(w, "Unable to decode session addCookie", err.Error())
		}
		if noteID != "" && userkey == key {
			err, note := getNote(noteID)
			if err {
				showResult(w, "Unable to find the note", note)
			} else {
				showResult(w, "Your note :", note)
			}
		} else {
			showResult(w, "Nothing provided/User not Found", ":(")
		}
	}
}

func reportNoteHandler(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		noteID := r.FormValue("noteid")
		userkey := r.FormValue("userkey")
		username, key, err := decodeSessionCookie(r)
		if err != nil {
			showResult(w, "Unable to decode session addCookie", err.Error())
		}
		if noteID != "" && userkey == key {
			err, note := getNote(noteID)
			if err {
				showResult(w, "Invalid Note ID", note)
			} else {
				err, noteUser := userNote(noteID)
				if err {
					showResult(w, "No user for Note ID", ":P")
				} else {
					if noteUser != username {
						showResult(w, "Not your Note", ":P")
					}
					err, message := addReport(noteID)
					if err {
						showResult(w, "Error adding a report", message)
					}
					showResult(w, "Note reported! we will review it shortly", message)
				}
			}
		} else {
			showResult(w, "Nothing provided/User not Found", ":(")
		}
	}
}

func viewReport(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		if !isAdmin(w, r) {
			showResult(w, "Become Admin first", ":/")
		} else {
			err, noteID := getAReport()
			if err {
				fmt.Fprintf(w, "No reports / error")
			} else {
				err, _ := updateReports(noteID)
				if err {
					fmt.Fprintf(w, "No reports / error")
				} else {
					_, note := getNote(noteID)
					fmt.Fprintf(w, note)
				}
			}
		}
	}
}

func flagHandler(w http.ResponseWriter, r *http.Request) {
	if !isLoggedIn(w, r) {
		showResult(w, "Log in First", "¯\\_(ツ)_/¯")
		return
	} else {
		userkey := r.FormValue("key")
		username, key, err := decodeSessionCookie(r)
		fmt.Println(username)
		fmt.Println(userkey == key)
		if err != nil {
			showResult(w, "Unable to decode session addCookie", err.Error())
		}
		fmt.Println(adminuser)
		if strings.Contains(username, adminuser) && userkey == key {
			dat, err := ioutil.ReadFile("flag.txt")
			if err != nil {
				showResult(w, "You should have got the flag", "Maybe trouble on our end?")
			}
			showResult(w, "Your flag is ", string(dat))
		} else {
			showResult(w, "You are not the admin!", "Bye bye!")
		}
	}
}

func logoutHandler(w http.ResponseWriter, r *http.Request) {
	unsetLocalSessionCookie(w, r)
	deleteCookie(w, r)
	showResult(w, "Successfully Logged out!", ":)")
}
