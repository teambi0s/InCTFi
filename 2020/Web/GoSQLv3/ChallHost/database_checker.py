import psycopg2
import os

func_arg_name = []

def send(payload):                                                                                           
    query = payload                                                                                           
    con = psycopg2.connect(host="127.0.0.1", database="gosqlv3", user="postgres", password="ILoveShirley", sslmode="disable")         
    con.autocommit=True                                                                                       
    curson=con.cursor()                                                                                       
    try:
	curson.execute(query)                                                                                    
    except:
	send("CREATE TABLE inctf2020(username character varying(20),go_to character varying(40));GRANT SELECT ON TABLE inctf2020 TO honeysingh;")
        send("insert into inctf2020 values('aaaaaa','./you_are_not_admin.php');")
        send("insert into inctf2020 values('admin','./feel_the_gosql_series.php');")
        send("insert into inctf2020 values('zamin','./you_are_not_admin.php');")
	
    try: 
    	rows = curson.fetchall()  
    	if(rows):
    		for row in rows:
			func_arg_name.append(row[0])
			func_arg_name.append(row[1]) 
    except:
	pass



send("select * from inctf2020")
if(func_arg_name==['aaaaaa', './you_are_not_admin.php', 'admin', './feel_the_gosql_series.php', 'zamin', './you_are_not_admin.php']):
	pass
else:
	send("drop table inctf2020;CREATE TABLE inctf2020(username character varying(20),go_to character varying(40));GRANT SELECT ON TABLE inctf2020 TO honeysingh;")
	send("insert into inctf2020 values('aaaaaa','./you_are_not_admin.php');")
	send("insert into inctf2020 values('admin','./feel_the_gosql_series.php');")
	send("insert into inctf2020 values('zamin','./you_are_not_admin.php');")
