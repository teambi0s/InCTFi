from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time

host = "http://172.17.0.2:8080"
flag = "inctf{8d739_csrf_is_fun_3d587ec9}"
cookie = {"name": "Token", "value": flag, "httpOnly": True, "path": "/api"}

def visit(url):
    driver = webdriver.Firefox(executable_path="./geckodriver")
    driver.set_page_load_timeout(10)
    try:
        driver.get(host + "/api")
        driver.add_cookie(cookie)
        driver.get(url)
        time.sleep(5)
        driver.quit()
        return True
    except:
        print ("Could not load the URL.")
        driver.quit()
        return False


if __name__ == "__main__":
    visit(input("URL: "))
