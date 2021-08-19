import requests, re, io, socket
from urllib.parse import urlparse, unquote_plus
import os



__ITEM_TYPE_IN_PATH = re.compile(r"(/[0-9+gITdhs])(/.+)")

deitemize = lambda x: __ITEM_TYPE_IN_PATH.sub(lambda m: m.groups()[1], x)
itemized = lambda x: __ITEM_TYPE_IN_PATH.match(x) is not None


class HoldsThings:
    """It's like a namedtuple, but you can't index by number and it's actually mutable."""

    def __init__(self, **kwargs):
        self.__dict__.update(kwargs)


def parse_url(url):
    res = urlparse(url)
    ret = HoldsThings(**res._asdict())
    if res.query:
        ret.path = res.path + "?" + res.query
    del ret.query
    if not ret.path:
        ret.path = "/"
    if "\t" in ret.path:
        ret.path, ret.query = ret.path.split("\t", 1)
    if itemized(ret.path):
        ret.path = deitemize(ret.path)
    return ret


class GopherAdapter(requests.adapters.BaseAdapter):
    def _netloc_to_tuple(self, netloc):
        host, sep, port = netloc.rpartition(":")
        if sep:  
            port = int(port)
        else:
            host = port
            port = 1010
        return (host, port)

    def _connect_and_read(self, parsed):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect(self._netloc_to_tuple(parsed.netloc))
        msg = parsed.path.replace('/_','')
        if hasattr(parsed, "query"):
            msg += "\t" + parsed.query
        msg += "\r\n"
        print(bytes(msg, 'utf-8'))
        s.sendall(bytes(msg, 'utf-8'))
        f = s.makefile("rb")
        res = b""
        data = f.readline()
        print(data)
        f.close()
        return res

    def _build_response(self, request, res):
        resp = requests.Response()
        resp.status_code = 400 if (res.startswith(b"3")
                                   or b"\r\n3" in res) else 200
        resp.headers = requests.structures.CaseInsensitiveDict({})
        resp.encoding = "utf-8"
        resp.raw = io.BytesIO(res)
        resp.url = request.url
        resp.req = request
        resp.connection = self
        return resp

    def send(self, request, **kwargs):
        assert request.method == "GET", f"You can't {request.method.lower!r} a Gopher resource!"
        parsed = parse_url(unquote_plus(request.url))
        res = self._connect_and_read(parsed)
        return self._build_response(request, res)