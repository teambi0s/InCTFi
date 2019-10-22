import json
import os

hash_dict = json.load(open("hashes.json"))
dirs = ["Admin", "ChallHost", "Handout"]

# Checking hash for flag
for i in range(2):
    a = os.popen("sha256sum " + dirs[i] + "/" + "flag").read().split(" ")[0]
    assert a == hash_dict["flag"]

# Checking hash for encrypt.py
for i in range(2):
    a = os.popen("sha256sum " + dirs[i] + "/" + "encrypt.py").read().split(" ")[0]
    assert a == hash_dict["Admin/encrypt.py"]

# Checking hash of encrypt.py for Handout directory
assert os.popen("sha256sum " + dirs[2] + "/" + "encrypt.py").read().split(" ")[0] == hash_dict["Handout/encrypt.py"]

# Checking hash for exploit_optimised.py
assert os.popen("sha256sum Admin/exploit_optimised.py").read().split(" ")[0] == hash_dict["exploit_optimised.py"]

# Checking hash for lsbit and run.sh
assert os.popen("sha256sum ChallHost/lsbit").read().split(" ")[0] == hash_dict["lsbit"]
assert os.popen("sha256sum ChallHost/run.sh").read().split(" ")[0] == hash_dict["run.sh"]
