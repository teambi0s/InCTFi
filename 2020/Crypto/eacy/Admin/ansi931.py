#!/usr/bin/env python

"""
A Python implementation of ANSI X9.31 using AES 128, following:
http://csrc.nist.gov/groups/STM/cavp/documents/rng/931rngext.pdf
Copyright (C) 2015 - Brian Caswell <bmc@lungetech.com>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
"""
from Crypto.Cipher import AES

class ANSI(object):
    BLOCK_SIZE = 16
    def __init__(self, seed=None):
        """
        Seed is V + Key + DT as a string
        """
        if seed is not None:
            assert len(seed) == 48
        else:
            seed = "zaybxcwdveuftgsh" + "0123456789abcdef" + "\x00" * 16

        self.V = seed[0:8]
        key = seed[8:32]
        self.DT = seed[32:]
        self.random_data = ''

        self.I = "\x00" * ANSI.BLOCK_SIZE
        self.aes_ctx = AES.new(key, AES.MODE_ECB)

    @staticmethod
    def _xor_string(value_1, value_2):
        assert len(value_1) == len(value_2)
        return ''.join(chr(ord(a) ^ ord(b)) for a, b in zip(value_1, value_2))

    def _get_block(self):

        self.I = self.aes_ctx.encrypt(self.DT)

        tmp = self._xor_string(self.I, self.V.rjust(len(self.I), "\x00"))
        self.random_data = self.aes_ctx.encrypt(tmp)

        tmp = self._xor_string(self.random_data, self.I)
        self.V = self.aes_ctx.encrypt(tmp)

        i = ANSI.BLOCK_SIZE - 1
        while i >= 0:
            out = (ord(self.DT[i]) + 1) % 256
            self.DT = self.DT[:i] + chr(out) + self.DT[i+1:]
            if out != 0:
                break
            i -= 1

    def get(self, size):
        assert isinstance(size, int)
        assert size > 0

        result = ''
        while len(result) < size:
            need = size - len(result)
            if not len(self.random_data):
                self._get_block()

            result += self.random_data[:need]
            self.random_data = self.random_data[need:]

        return result

if __name__ == "__main__":
    ansi_obj = ANSI("\x00"*48)
    print ansi_obj.get(8)
