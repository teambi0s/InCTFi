import json
import os

hash_dict = json.load(open("hashes.json"))
dirs = ["Admin", "ChallHost", "Handout"]

# Checking hash for secret.py and cookiegen.py
for i in range(2):
    a = os.popen("sha256sum " + dirs[i] + "/" + "secret.py").read().split(" ")[0]
    assert a == hash_dict["secret.py"]
    a = os.popen("sha256sum " + dirs[i] + "/" + "cookiegen.py").read().split(" ")[0]
    assert a == hash_dict["Admin/cookiegen.py"]
    a = os.popen("sha256sum " + dirs[i] + "/" + "service.py").read().split(" ")[0]
    assert a == hash_dict["service.py"]

# Checking hash for gen_prime.py
assert os.popen("sha256sum " + "Admin" + "/" + "gen_prime.py").read().split(" ")[0] == hash_dict["gen_prime.py"]

# Checking hash for cookiegen.py and service.py for `Handout` dir
a = os.popen("sha256sum " + "Handout" + "/" + "cookiegen.py").read().split(" ")[0]
assert a == hash_dict["Handout/cookiegen.py"]
a = os.popen("sha256sum " + "Handout" + "/" + "service.py").read().split(" ")[0]
assert a == hash_dict["service.py"]

"""
TODO:
1. Add blockcipher and run.sh for hosting challenge on a server
2. Add hash check for ChallHost/blockcipher and ChallHost/run.sh
3. Set r/x permission restrictions to check_hash.py and hashes.json
"""
