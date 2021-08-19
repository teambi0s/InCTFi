import socket
import sys

host = '127.0.0.1'
port = 6379  # web

print('# Creating socket')

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print('Failed to create socket')
    sys.exit()

try:
    remote_ip = socket.gethostbyname( host )
except socket.gaierror:
    print('Hostname could not be resolved. Exiting')
    sys.exit()

s.connect((remote_ip , port))
request = b"get%20AAA\r\n"
try:
    s.sendall(request)
except socket.error:
    print ('Send failed')
    sys.exit()
reply = s.recv(4096)
print(str(reply))