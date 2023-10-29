#include <iostream>
#include <string.h>
#include <sodium.h>
using namespace std;

void print(unsigned char *str, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%02X ", str[i]);
    }
    printf("\n");
}

int main()
{
    if (sodium_init() == -1)
        return 1;

    unsigned char buf[] = "test";
    size_t buf_len = strlen((char *)buf);
    unsigned char key[crypto_auth_KEYBYTES];
    unsigned char mac[crypto_auth_BYTES];

    cout << "Buffer: ";
    print(buf, buf_len);

    size_t buf_hash_len = crypto_hash_sha256_BYTES;
    unsigned char buf_hash[buf_hash_len];
    crypto_hash_sha256(buf_hash, buf, buf_len);
    cout << "Buffer after hashed: ";
    print(buf_hash, buf_hash_len);

    crypto_auth_keygen(key);
    crypto_auth(mac, buf, buf_len, key);
    cout << "MAC: ";
    print(mac, crypto_auth_BYTES);
    cout << "with the key: ";
    print(key, crypto_auth_KEYBYTES);
    if (crypto_auth_verify(mac, buf, buf_len, key) == 0)
    {
        cout << "Verified" << endl;
    }
    else
    {
        cout << "Not verified" << endl;
    }

    return 0;
}
