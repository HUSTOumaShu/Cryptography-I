from typing import Iterable
from string import printable
from math import log10 as log
from itertools import product

ENGLISH_FREQ = {
    'A':  8.55,    'K':  0.81,    'U':  2.68,
    'B':  1.60,    'L':  4.21,    'V':  1.06,
    'C':  3.16,    'M':  2.53,    'W':  1.83,
    'D':  3.87,    'N':  7.17,    'X':  0.19,
    'E': 12.10,    'O':  7.47,    'Y':  1.72,
    'F':  2.18,    'P':  2.07,    'Z':  0.11,
    'G':  2.09,    'Q':  0.10,
    'H':  4.96,    'R':  6.33,
    'I':  7.33,    'S':  6.73,
    'J':  0.22,    'T':  8.94,
}


def get_score(s: bytes, replace: bool = True, puncts: Iterable[bytes] = b',. \'"\n') -> float:
    if replace:
        for b in puncts:
            if type(b) is int:
                b = chr(b).encode()
            s = s.replace(b, b'')
    return sum(ENGLISH_FREQ[char] * (log(s.count(char.encode()) + s.count(char.lower().encode()) + 1e-12) - log(len(s)))
               for char in ENGLISH_FREQ)


def stream_xor(b1: bytes, b2: bytes) -> bytes:
    return bytes(a ^ b for a, b in zip(b1, b2))


def brute_force(cipher: bytes, c_min: int = 1, c_max: int = 4, charset: Iterable[bytes] = printable.encode()) -> (bytes, bytes):
    max_score, max_decrypted, max_key = None, None, None
    for c_len in range(c_min, c_max+1):
        for key in product(charset, repeat=c_len):
            if (type(key) is int):
                key = bytes(key)
            else:
                key = b''.join(key)
            decrypted = stream_xor(cipher, key)
            score = get_score(decrypted)
            if max_score is None or score > max_score:
                max_score, max_decrypted, max_key = score, decrypted, key
    return max_score, max_decrypted, max_key


brute_force(
    b'1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736')
