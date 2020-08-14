package main

import (
	"crypto/md5"
	"encoding/base64"
	"encoding/hex"
	"fmt"
	"math/rand"
	"net/http"
	"os"
	"strings"
	"time"
	"io/ioutil"
	_ "github.com/go-sql-driver/mysql"
	"github.com/gorilla/mux"
	"github.com/gorilla/sessions"
)

var adminuser string
var adminpassword string
var isAdminReg = false

var letters = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
var (
	// key must be 16, 24 or 32 bytes long (AES-128, AES-192 or AES-256)
	key   = []byte(randSeq(32))
	store = sessions.NewCookieStore(key)
)

type MessageData struct {
	Message string
	Subtext string
}

func randSeq(n int) string {
	b := make([]rune, n)
	for i := range b {
		b[i] = letters[rand.Intn(len(letters))]
	}
	return string(b)
}

func decodeSessionCookie(r *http.Request) (string, string, error) {
	sessionCookie, err := r.Cookie("Session")
	if err != nil {
		return "", "", err
	}
	tmp := strings.Split(sessionCookie.String(), "Session=")
	username, err := base64.StdEncoding.DecodeString(tmp[1])
	if err != nil {
		return "", "", err
	}
	userKey := genKey(string(username))
	return string(username), userKey, nil
}

func addCookie(w http.ResponseWriter, r *http.Request, username string) {
	val := base64.StdEncoding.EncodeToString([]byte(username))
	c := &http.Cookie{
		Name:  "Session",
		Value: val,
		Path:  "/",
	}
	http.SetCookie(w, c)
}

func deleteCookie(w http.ResponseWriter, r *http.Request) {
	c := &http.Cookie{
		Name:   "Session",
		Value:  "",
		Path:   "/",
		MaxAge: -1,
	}
	http.SetCookie(w, c)
}

func isLoggedIn(w http.ResponseWriter, r *http.Request) bool {
	session, _ := store.Get(r, "cookie-name")
	if auth, ok := session.Values["authenticated"].(bool); !ok || !auth {
		//http.Error(w, "Forbidden", http.StatusForbidden)
		return false
	}
	return true
}

func isAdmin(w http.ResponseWriter, r *http.Request) bool {
	session, _ := store.Get(r, "cookie-name")
	if auth, ok := session.Values["is_admin"].(bool); !ok || !auth {
		//http.Error(w, "Forbidden", http.StatusForbidden)
		return false
	}
	return true
}

func setLocalSessionCookie(w http.ResponseWriter, r *http.Request) {
	rand.Seed(time.Now().UnixNano())
	session, _ := store.Get(r, "cookie-name")
	session.Values["authenticated"] = true
	session.Values["is_admin"] = false
	session.Save(r, w)
}

func setAdminSessionCookie(w http.ResponseWriter, r *http.Request) {
	rand.Seed(time.Now().UnixNano())
	session, _ := store.Get(r, "cookie-name")
	session.Values["authenticated"] = true
	session.Values["is_admin"] = true
	session.Save(r, w)
}

func unsetLocalSessionCookie(w http.ResponseWriter, r *http.Request) {
	session, _ := store.Get(r, "cookie-name")
	session.Values["authenticated"] = false
	session.Values["is_admin"] = false
	session.Save(r, w)
}

func genKey(username string) string {
	secret, err := ioutil.ReadFile("secret.txt")
	if err != nil {
		fmt.Println("Read File Error")
	}
	hashh := md5.New()
	hashh.Write([]byte(string(secret) + username))
	return hex.EncodeToString(hashh.Sum(nil))
}

func setupRouting(r *mux.Router) {
	r.HandleFunc("/", staticHandler)
	// Login Functions
	userRouter := r.PathPrefix("/user").Subrouter()
	userRouter.HandleFunc("/", staticHandler)
	userRouter.HandleFunc("/login", loginpageHandler)
	userRouter.HandleFunc("/register", registerpageHandler)
	userRouter.HandleFunc("/logout", logoutHandler)
	userRouter.HandleFunc("/login/api", loginHandler)
	userRouter.HandleFunc("/register/api", registerHandler)
	// Note Functions
	noteRouter := r.PathPrefix("/note").Subrouter()
	noteRouter.HandleFunc("/", staticHandler)
	noteRouter.HandleFunc("/view", viewNotepageHandler)
	noteRouter.HandleFunc("/view/api", viewNoteHandler)
	noteRouter.HandleFunc("/add", addNotepageHandler)
	noteRouter.HandleFunc("/add/api", addNoteHandler)
	// Report Bug Functions
	reportRouter := r.PathPrefix("/report").Subrouter()
	reportRouter.HandleFunc("/", staticHandler)
	reportRouter.HandleFunc("/view/", viewReport)
	reportRouter.HandleFunc("/add", reportNotepageHandler)
	reportRouter.HandleFunc("/add/api", reportNoteHandler)
	// Flag
	flagRouter := r.PathPrefix("/inCTF").Subrouter()
	flagRouter.HandleFunc("/flag", flagHandler)
	// Admin
	adminRouter := r.PathPrefix("/admin").Subrouter()
	adminRouter.HandleFunc("/register", adminRegisterpageHandler)
	adminRouter.HandleFunc("/login", adminLoginpageHandler)
	adminRouter.HandleFunc("/register/api", adminRegisterHandler)
	adminRouter.HandleFunc("/login/api", adminLoginHandler)
}

func main() {
	// Create the Router
	r := mux.NewRouter()
	// Open DB connection
	err := openDBConnection()
	if err {
		fmt.Println("Unable to open database connection")
		os.Exit(-1)
	}
	// Create the table
	err = createUserTable()
	if err {
		fmt.Println("Unable to create user Table")
		os.Exit(-1)
	}
	err = createNotesTable()
	if err {
		fmt.Println("Unable to create notes Table")
		os.Exit(-1)
	}
	err = createReportsTable()
	if err {
		fmt.Println("Unable to create Reports Table")
		os.Exit(-1)
	}
	// Setup all the routes
	setupRouting(r)
	fmt.Println("Starting")
	http.ListenAndServe(":8080", r)
}
