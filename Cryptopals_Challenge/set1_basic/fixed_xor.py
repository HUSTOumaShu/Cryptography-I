from binascii import unhexlify, hexlify


def xor(str1, str2):
    str1 = unhexlify(hex1)
    str2 = unhexlify(hex2)
    return hexlify(bytes([a ^ b for a, b in zip(str1, str2)]))


hex1 = input('Enter hex string 1: ')
hex2 = input('Enter hex string 2: ')
str = xor(hex1, hex2)
print(str)
