#include <iostream>
#include <string.h>
#include <sodium.h>
#include <assert.h>
using namespace std;

void print(unsigned char *str, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%02X ", str[i]);
    }
    printf("\n");
}

// Algorithms
/* Initialization
    k <- HChaCha20(K, N[0..16])
    n <- N[16..24] (nonce)
    i <- 1 (counter)
*/
/* Encryption
    c, mac <- ChaCha20Poly1305-IETF(key = k, nonce = i || n, msg = T || {0} * 63 || M)
    n <- n ^ mac[0..8]
    i <- (i + 1) & 0xffffffff
    if i = 0:
    rekey()
*/
/* Rekey
    k || n <- ChaCha20-IETF(key = k, nonce = i || n, msg = k || n)
    i <- 1
*/

// Encryption
/*
    void crypto_secretstream_xchacha20poly1305_keygen
            (unsigned char k[crypto_secretstream_xchacha20poly1305_KEYBYTES]);
generate a random key

    int crypto_secretstream_xchacha20poly1305_init_push(
        crypto_secretstream_xchacha20poly1305_state *state,
        unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES],
        const unsigned char k[crypto_secretstream_xchacha20poly1305_KEYBYTES]);
initializes state using the key and IV stored in header

    int crypto_secretstream_xchacha20poly1305_push(
        crypto_secretstream_xchacha20poly1305_state *state,
        unsigned char *c, unsigned long long *clen_p,
        const unsigned char *m, unsigned long long mlen,
        const unsigned char *ad, unsigned long long adlen, unsigned char tag);
encrypts mlen bytes from m to c, using state and key, (ad)

    void crypto_secretstream_xchacha20poly1305_rekey(
        crypto_secretstream_xchacha20poly1305_state *state);
rekey state

*/

// Decryption
/*
    int crypto_secretstream_xchacha20poly1305_init_pull(
        crypto_secretstream_xchacha20poly1305_state *state,
        const unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES],
        const unsigned char k[crypto_secretstream_xchacha20poly1305_KEYBYTES]);
initializes state using the key and IV stored in header
return 0 on success, -1 if header is invalid

    int crypto_secretstream_xchacha20poly1305_pull(
        crypto_secretstream_xchacha20poly1305_state *state,
        unsigned char *m, unsigned long long *mlen_p,
        unsigned char *tag_p,
        const unsigned char *c, unsigned long long clen,
        const unsigned char *ad, unsigned long long adlen);

*/

int main()
{
    if (sodium_init() == -1)
    {
        return 1;
    }

#define MESSAGE1 ((const unsigned char *)"Don't use the key more than once!")
#define MESSAGE1_LEN 38
#define CIPHERTEXT1_LEN (crypto_secretstream_xchacha20poly1305_ABYTES + MESSAGE1_LEN)

#define MESSAGE2 ((const unsigned char *)"The length of key must be more than 80 bit.")
#define MESSAGE2_LEN 56
#define CIPHERTEXT2_LEN (crypto_secretstream_xchacha20poly1305_ABYTES + MESSAGE2_LEN)

#define MESSAGE3 ((const unsigned char *)"The length of nonce must be 192 bit.")
#define MESSAGE3_LEN 40
#define CIPHERTEXT3_LEN (crypto_secretstream_xchacha20poly1305_ABYTES + MESSAGE3_LEN)

    crypto_secretstream_xchacha20poly1305_state state;
    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    unsigned char c1[CIPHERTEXT1_LEN], c2[CIPHERTEXT2_LEN], c3[CIPHERTEXT3_LEN];

    // Generate a random key
    crypto_secretstream_xchacha20poly1305_keygen(key);
    print(key, crypto_secretstream_xchacha20poly1305_KEYBYTES);

    /*
        Encryption
    */
    // Initialize state
    crypto_secretstream_xchacha20poly1305_init_push(&state, header, key);

    // Encrypt 3 messages
    crypto_secretstream_xchacha20poly1305_push(&state, c1, NULL, MESSAGE1, MESSAGE1_LEN, NULL, 0, 0);
    crypto_secretstream_xchacha20poly1305_push(&state, c2, NULL, MESSAGE2, MESSAGE2_LEN, NULL, 0, 0);
    crypto_secretstream_xchacha20poly1305_push(&state, c3, NULL, MESSAGE3, MESSAGE3_LEN, NULL, 0, crypto_secretstream_xchacha20poly1305_TAG_FINAL);

    // Print ciphertext
    print(c1, CIPHERTEXT1_LEN);
    print(c2, CIPHERTEXT2_LEN);
    print(c3, CIPHERTEXT3_LEN);

    /*
        Decryption
    */
    unsigned char tag;
    unsigned char m1[MESSAGE1_LEN], m2[MESSAGE2_LEN], m3[MESSAGE3_LEN];
    if (crypto_secretstream_xchacha20poly1305_init_pull(&state, header, key) != 0)
    {
        cout << "Header is invalid" << endl;
        return 1;
    }

    // Decrypt 3 messages
    if (crypto_secretstream_xchacha20poly1305_pull(&state, m1, NULL, &tag, c1, CIPHERTEXT1_LEN, NULL, 0) != 0)
    {
        cout << "c1 is invalid" << endl;
        return 1;
    }
    assert(tag == 0);
    if (crypto_secretstream_xchacha20poly1305_pull(&state, m2, NULL, &tag, c2, CIPHERTEXT2_LEN, NULL, 0) != 0)
    {
        cout << "c2 is invalid" << endl;
        return 1;
    }
    assert(tag == 0);
    if (crypto_secretstream_xchacha20poly1305_pull(&state, m3, NULL, &tag, c3, CIPHERTEXT3_LEN, NULL, 0) != 0)
    {
        cout << "c3 is invalid" << endl;
        return 1;
    }
    assert(tag == crypto_secretstream_xchacha20poly1305_TAG_FINAL);
    printf("After decryption:\n");
    print(m1, MESSAGE1_LEN);
    print(m2, MESSAGE2_LEN);
    print(m3, MESSAGE3_LEN);

    return 0;
}
