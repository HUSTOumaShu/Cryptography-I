from binascii import hexlify, unhexlify
from itertools import cycle


def hex_xor(hex1: hex, hex2: hex) -> hex:
    return hexlify(bytes([a ^ b for a, b in zip(unhexlify(hex1), cycle(unhexlify(hex2)))]))
