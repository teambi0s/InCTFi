f = open("/home/ph03n1x/top500Domains.csv").readlines()[1:]
for i in range(500) :
    f[i] = f[i].strip().split(",")[1].strip("\"")

for i in range(500) :
    if not f[i].startswith("www") :
        f[i] = "www." + f[i]

s = lambda x : sum([ord(i) for i in x])
d = dict((i,[]) for i in range(37))
for site in f :
    tmp = s(site.split(".")[1])
    d[tmp%37].append(site)

site_list = [d[i][2:5] for i in range(37)]
for i in range(37) :
    for j in range(3) :
        main_sites.append(site_list[i][j])

import random
for site in main_sites :
    site_pass[site] = obj.gen_pass(site,master_pass, random.randint(8,12))


flag = "inctf{Always_h4v3_a_statistic4l_3y3_wh3n_it_com3s_to_weakn3ss3s}"

f = open("dict.py","w")
f.write("flag = \"")
f.write(flag + "\"\n")
f.write("site_pass = ")
f.write(str(site_pass) + "\n")
f.close()

