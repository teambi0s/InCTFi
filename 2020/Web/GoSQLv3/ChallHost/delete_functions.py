import psycopg2

func_arg_name = []

def send(payload):                                                                                           
    query = payload                                                                                           
    con = psycopg2.connect(host="127.0.0.1", database="gosqlv3", user="honeysingh", sslmode="disable")         
    con.autocommit=True                                                                                       
    curson=con.cursor()                                                                                       
    curson.execute(query)                                                                                    
    try: 
    	rows = curson.fetchall()  
    	if(rows):
    		for row in rows:
			func_arg_name.append(row[1])
			func_arg_name.append(row[4]) 
    except:
	pass

send("""select n.nspname as function_schema,
       p.proname as function_name,
       l.lanname as function_language,
       case when l.lanname = 'internal' then p.prosrc
            else pg_get_functiondef(p.oid)
            end as definition,
       pg_get_function_arguments(p.oid) as function_arguments,
       t.typname as return_type
from pg_proc p
left join pg_namespace n on p.pronamespace = n.oid
left join pg_language l on p.prolang = l.oid
left join pg_type t on t.oid = p.prorettype 
where n.nspname not in ('pg_catalog', 'information_schema')
order by function_schema,
         function_name;""")


for i in range(0,len(func_arg_name),2):
	send("drop function "+func_arg_name[i]+"("+func_arg_name[i+1]+");")
