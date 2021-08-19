from os import urandom as securegen
from json import load
from binascii import hexlify, unhexlify
from shutil import rmtree
import mysql.connector
from base64 import b64encode as encode
from mysql.connector import errorcode
from os import makedirs, path, remove, listdir, walk
from dataclasses import dataclass

with open("/opt/blackStab/config.json",'r') as file:
  CONFIG = load(file)

@dataclass
class VMStruct:
    name: str
    tag: str
    image: str
    udpPorts: list
    tcpPorts: list
    cpu: int = 2
    ram: int = 4

class console:
    def __init__(self):
        self.region = CONFIG['region'].encode()
        self.statuscount = 25
        self.images = {
            0: "Archlinux",
            1: "Ubuntu 16.04",
            2: "Ubuntu 18.04",
            3: "CentOS 7",
            4: "Oracle Linux 6",
            5: "OpenSUSE by SUSE",
            6: "Windows Server 2019 LTSC"
        }
        return

    def createVM(self, funds, account, name, tag, imageid, key, keyname):
        if(not (funds > 100)):
            return 2
        if(not path.exists(path.join(self.region, account, name))):
            makedirs(path.join(self.region, account, name))
        vm = VMStruct(name=name, tag=tag, image=self.images[imageid], tcpPorts=[22,80] , udpPorts=[53])
        if(not path.exists(path.join(self.region, account, name, name + b".details"))):
            open(path.join(self.region, account, name, name + b'.details'), 'w').write(hexlify(str(vm).encode()).decode())
            open(path.join(self.region, account, name, keyname),'w').write(key.decode())
        else:
            return 1
        return 0

    def getmykey(self, account, name, keyname):
        if(not path.exists(path.join(self.region, account))):
            return "You have no VMs associated with this account"
        elif(path.exists(path.join(self.region, account, name, keyname)) and path.isfile(path.join(self.region, account, name, keyname))):
            key=open(path.join(self.region, account, name, keyname)).read()
            return key
        elif(path.exists(path.join(self.region, account, name))):
            keys = b', '.join(list(filter(lambda x: (b'.details' not in x), listdir(path.join(self.region, account, name)))))
            keylist = """
        You dont't have the key {} associated to the VM {}
        Here is the list of keys associated with the VM:
        [{}]
        """.format(keyname.decode(), name.decode(), keys.decode())
            return keylist
        else:
            return "VM with the requested name not found"

    def modifyFirewall(self, account, name, proto, port, operation):
        if(not path.exists(path.join(self.region, account, name))):
            return 2
        else:
            pass
        vm = eval(unhexlify(open(path.join(self.region, account, name, name + b".details")).read()))
        if(operation == 1):
            if(not (port in eval("vm.{}Ports".format(proto)))):
                eval("vm.{}Ports".format(proto)).append(port)
                eval("vm.{}Ports".format(proto)).sort()
                open(path.join(self.region, account, name, name + b".details"), 'w').write(hexlify(str(vm).encode()).decode())
                return 0
            else:
                return 1
        else:
            if(port in eval("vm.{}Ports".format(proto))):
                eval("vm.{}Ports".format(proto)).remove(port)
                open(path.join(self.region, account, name, name + b".details"), 'w').write(hexlify(str(vm).encode()).decode())
                return 0
            else:
                return 1

    def modifyShape(self, account, balance, name, resource, count, operation):
        prices = {
                'ram': 30,
                'cpu': 70,
        }

        if(not path.exists(path.join(self.region, account, name))):
            return 2
        else:
            pass

        vm = eval(unhexlify(open(path.join(self.region, account, name, name + b".details")).read()))
        cost = prices[resource] * count
        if(operation == 1):
            if(cost > balance):
                return 1
            else:
                pass

            exec("vm.{} += count".format(resource))
            open(path.join(self.region, account, name, name + b".details"), 'w').write(hexlify(str(vm).encode()).decode())
            return 0

        else:
            if(eval("vm.{}".format(resource)) <= count):
                return 1
            else:
                pass
            exec("vm.{} -= count".format(resource))
            open(path.join(self.region, account, name, name + b".details"), 'w').write(hexlify(str(vm).encode()).decode())
            return 0

    def deleteVM(self, account, name):
        if(not path.exists(path.join(self.region, account, name))):
            return 1
        else:
            rmtree(path.join(path.join(self.region, account, name)))
            return 0

    def removeAccount(self, account, challenge):
        if(not challenge):
            return 2
        else:
            pass
        if(path.exists(path.join(self.region, account))):
            rmtree(path.join(self.region, account))
            return 0
        else:
            return 1

    def statusofVM(self, account, name):
        if(not path.exists(path.join(self.region, account, name))):
            data = "The VM with the name {} does not exist".format(name.decode())
            return data
        else:
            pass

        vm = eval(unhexlify(open(path.join(self.region, account, name, name + b".details")).read()))
        data = """
        VM Name: {}
        VM Tag: {} // encoded for security reasons
        Operating System: {}
        Associated to Account: {}
        UDP Ports Open: {}
        TCP Ports Open: {}
        Specifications: Number of CPUs are {} and the RAM is {} GB
        """.format(vm.name.decode(), encode(vm.tag).decode(), vm.image,account.decode(), str(vm.udpPorts), str(vm.tcpPorts), str(vm.cpu), str(vm.ram))
        return data

    def listmyVMs(self, account):
        if(path.exists(path.join(self.region, account))):
            if(len(listdir(path.join(self.region, account))) == 0):
                return 0
            else:
                pass
        else:
            return 0
        vmnames = "\n\t" + '\n\t'.join(listdir(path.join(self.region.decode(), account.decode())))
        return vmnames

    def expandregion(self):
        vms = []
        for account in listdir(self.region):
            for name in listdir(path.join(self.region, account)):
                vms.append((self.statusofVM(account=account, name=name), path.join(self.region, account, name)))
                vms.sort(key=lambda x: path.getatime(path.join(self.region, account, x[1])), reverse=True)
                if(len(vms) > self.statuscount):
                    vms = vms[:self.statuscount]
        return '\n'.join(list(map(lambda vm: vm[0], vms)))

class accounts:
    def __init__(self):
        self.cnx = mysql.connector.connect(host="localhost",user=CONFIG['db_user'],password=CONFIG['db_pass'],database=CONFIG['database'], auth_plugin='mysql_native_password')
        return

    def register(self, email, username, password):
        cnx = self.cnx
        cursor = cnx.cursor()
        cursor.execute('SELECT * from users where email="{}"'.format(email))
        acc_match = cursor.fetchall()
        if(len(acc_match)):
            return 1
        elif(len(password) < 12):
            return 2
        else:
            pass
        _register = ("INSERT INTO users "
                    "(email, username, password, credits) "
                    "VALUES (%s, %s, %s, %s)")
        cursor.execute(_register, (email, username, password, 1000))
        cnx.commit()
        return 0

    def check_login(self, email, password):
        cnx = self.cnx
        cursor = cnx.cursor()
        cursor.execute('SELECT * from users where email="{}"'.format(email))
        acc_match = cursor.fetchall()
        if(not len(acc_match)):
            return 1
        else:
            pass
        if(not (acc_match[0][2] == password)):
            return 2
        else:
            pass
        return 0
    
    def showCredits(self, email):
        cnx = self.cnx
        cursor = cnx.cursor()
        cursor.execute('SELECT credits from users where email="{}"'.format(email))
        _credits = cursor.fetchall()[0][0]
        return _credits

    def useCredits(self, email, credits):
        cnx = self.cnx
        cursor = cnx.cursor()
        _credits = self.showCredits(email=email)
        cursor.execute('UPDATE users SET credits={} WHERE email="{}"'.format((_credits-credits), email))
        cnx.commit()

    def removeAccount(self, email, password):
        cnx = self.cnx
        cursor = cnx.cursor()
        cursor.execute('SELECT password from users where email="{}"'.format(email))
        acc_match = cursor.fetchall()
        if(not (acc_match[0][0] == password)):
            return 1
        else:
            pass   
        _remove = ('DELETE FROM users where email="{}"'.format(email))
        cursor.execute(_remove)
        cnx.commit()
        return 0