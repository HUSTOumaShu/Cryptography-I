from binascii import unhexlify
from base64 import b64encode


# Convert hex string to utf-8 string and convert to base64
def hex_to_base64(str_hex):
    return b64encode(unhexlify(str_hex))


str_hex = input('Enter hex string: ')
print(hex_to_base64(str_hex))
print(unhexlify(str_hex))
