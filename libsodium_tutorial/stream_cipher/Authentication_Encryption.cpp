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

    unsigned char buf[] = "Hello World!";
    print(buf, strlen((char *)buf));

    size_t buf_len = strlen((char *)buf);
    size_t cipher_len = buf_len + crypto_secretbox_MACBYTES;
    unsigned char key[crypto_secretbox_KEYBYTES];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    unsigned char cipher[cipher_len];

    crypto_secretbox_keygen(key);
    randombytes_buf(nonce, sizeof nonce);
    crypto_secretbox_easy(cipher, buf, buf_len, nonce, key); // encrypt
    print(cipher, cipher_len);

    unsigned char decrypted[buf_len];
    if (crypto_secretbox_open_easy(decrypted, cipher, cipher_len, nonce, key) != 0) // decrypt
    {
        cout << "Decryption failed" << endl;
    }
    else
    {
        print(decrypted, buf_len);
    }

    return 0;
}
