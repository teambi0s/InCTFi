#!/usr/bin/env python3
# coding: utf-8

from os import environ, path, makedirs, execvp
from time import sleep
import fcntl
import jinja2
import logging
import re
import socket
import struct
import sys

LOG_LEVEL = environ.get('LOG_LEVEL', 'INFO').upper()
ZONE_TEMPLATE = environ.get("ZONE_TEMPLATE", "./zone.j2")
NAMED_TEMPLATE = environ.get("NAMED_TEMPLATE", "./named.conf.j2")
NAMED_OUTPUT = environ.get("NAMED_RENDERED", "/data/bind/etc/named.conf")
TTL = environ.get("ZONE_TTL", "10s")
NS = environ.get("ZONE_NS", "ns")
DOMAIN = environ["ZONE_DOMAIN"] # Domain without leading dot
HOSTS = environ["ZONE_HOSTS"].split() # Space seperated list
ZONE_OUTPUT = environ.get("ZONE_RENDERED", "/data/bind/etc/{}.zone".format(DOMAIN))

# Dummy socket used for fcntl functions
_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

logging.basicConfig(level=LOG_LEVEL, format="[%(levelname)s %(asctime)s] %(message)s", datefmt="%m-%d %H:%M:%S")
logger = logging.getLogger('zonerender')

def render(zone_template, **context):
    dirname, filename = path.split(zone_template)
    env = jinja2.Environment(
        loader=jinja2.FileSystemLoader(dirname or './')
    )
    return env.get_template(filename).render(**context)

def writefile(filepath, text):
    makedirs(path.dirname(filepath), exist_ok=True)
    with open(filepath, 'w') as f:
        f.write(text)

def _ifctl(ifname, code):
    if isinstance(ifname, str):
        ifname = ifname.encode('utf-8')

    return fcntl.ioctl(
        _socket.fileno(),
        code,
        struct.pack('256s', ifname[:15])
    )

def ifaddr(ifname):
    return '.'.join(str(x) for x in _ifctl(ifname, 0x8915)[20:24]) # SIOCGIFADDR

def parsehosts(hosts):
    result = dict()
    for host in hosts:
        m = re.fullmatch(r'([\w.]+)=([0-9.]+)', host)
        if m is None:
            raise ValueError("host entry '{}' is not valid; must be <name>=<ip address>".format(host))
        name, address = m.group(1, 2)
        result[name] = address
    return result

if __name__ == "__main__":
    hosts = parsehosts(HOSTS)
    if NS not in hosts:
        hosts[NS] = ifaddr("eth0")

    # Render the zone file
    zone_text = render(ZONE_TEMPLATE, ns=NS, hosts=hosts, domain=DOMAIN, ttl=TTL)
    writefile(ZONE_OUTPUT, zone_text)
    logging.info("Rendered zone file for %s", DOMAIN)
    logging.debug(zone_text)

    # Render the named.conf file
    named_text = render(NAMED_TEMPLATE, domain=DOMAIN)
    writefile(NAMED_OUTPUT, named_text)
    logging.info("Rendered named.conf")
    logging.debug(named_text)

    # Exec the next program
    logging.info("Done rendering zone files. Now running '%s'" % " ".join(sys.argv[1:]))
    if len(sys.argv) > 1:
        execvp(sys.argv[1], sys.argv[1:])