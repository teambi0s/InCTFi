from Crypto.Util.number import *
from ansi931 import ANSI
from os import urandom
import ecc
import time

class ecprng:
    # Curve P-256; source: https://safecurves.cr.yp.to/
    p = 2**256 - 2**224 + 2**192 + 2**96 - 1
    a = p-3
    b = 41058363725152142129326129780047268409114441015993725554835256314039467401291
    ec = ecc.CurveFp(p, a, b)

    _Px = 115113149114637566422228202471255745041343462839792246702200996638778690567225
    _Py = 88701990415124583444630570378020746694390711248186320283617457322869078545663
    Point_P = ecc.Point(ec, _Px, _Py)

    _Qx = 75498749949015782244392151836890161743686522667385613237212787867797557116642
    _Qy = 19586975827802643945708711597046872561784179836880328844627665993398229124361
    Point_Q = ecc.Point(ec, _Qx, _Qy)

    def __init__(self, seed):
        self.seed = seed
        if self.seed:
            assert len(long_to_bytes(self.seed)) == 32

    def update_seed(self, intermediate_state_S_1):
        self.seed = (intermediate_state_S_1 * ecprng.Point_P).x()
        assert len(long_to_bytes(self.seed)) == 32

    def ec_generate(self):
        intermediate_state_S_1 = (self.seed * ecprng.Point_P).x()
        self.update_seed(intermediate_state_S_1)
        r_1 = long_to_bytes((intermediate_state_S_1 * ecprng.Point_Q).x())[-30:]
        r_2 = long_to_bytes((self.seed * ecprng.Point_Q).x())[-30:][:2]
        assert len(r_1 + r_2) == 32
        return bytes_to_long(r_1 + r_2)

class prng:

    prng_output_index = 0

    def __init__(self, seed, key, one_state_rng):
        self.prng_seed = seed
        self.prng_key = key
        self.one_state_rng = one_state_rng
        self.prng_temporary = ""
        prng.prng_output_index = 0

        # Replace the below value with bytes_to_long(os.urandom(32)): Replaced May-24
        # random_seed = 34284683824539919476821362892602703208482911918738124857105009690976372578814
        random_seed = bytes_to_long(urandom(32))
        self.ecprng_obj = ecprng(random_seed)

        assert len(long_to_bytes(self.prng_seed)) == 8
        assert len(long_to_bytes(self.prng_key)) == 24
        assert self.one_state_rng == True or self.one_state_rng == False

    def prng_reseed(self):
        self.prng_temporary = long_to_bytes(self.ecprng_obj.ec_generate())
        assert len(self.prng_temporary) == 32
        self.prng_seed = self.prng_temporary[:8]
        prng.prng_output_index = 8
        self.prng_key = self.prng_temporary[8:]
        prng.prng_output_index = 32
        return bytes_to_long(self.prng_temporary)

    def prng_generate(self):
        _time = time.time()
        prng.prng_output_index = 0
        if not self.one_state_rng:
            self.prng_reseed()
        ansi_obj = ANSI(self.prng_seed + self.prng_key + long_to_bytes(_time).rjust(16, "\x00"))
        while prng.prng_output_index <= 0x1f:
            self.prng_temporary += ANSI.get(8)
            prng.prng_output_index += 8
        return bytes_to_long(self.prng_temporary)