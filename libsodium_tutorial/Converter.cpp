#include <iostream>
#include <sodium.h>
#include <string.h>
using namespace std;

// Constant-time test for equality
/*
    void sodium_memcmp(const void * const b1_, const void *const b2_, size_t len)
return 0 if the len bytes pointed by b1_ match to b2_, otherwise return -1
*/

// Hexadecimal encode/decode
/*
    char* sodium_bin2hex(char * const hex, const size_t hex_maxlen,
                        const unsigned char * const bin, const size_t bin_len)
hex_maxlen >= bin_len*2 + 1 bytes
convert bin to hex and return hex

    char *sodium_hex2bin(unsigned char * const bin, const size_t bin_maxlen,
                        const char * const hex, const size_t hex_len,
                        const char * const ignore, size_t * const bin_len,
                        const char ** const hex_end)
bin_maxlen >= hex_len/2 bytes
convert hex to bin and return bin
ignore is the string includes characters to ignore, example ": "
hex_end should be null
return 0 if success, otherwise -1
*/

// Base64 encode/decode
/*
    char* sodium_bin2base64(char * const b64, const size_t b64_maxlen,
                    const unsigned char * const bin, const size_t bin_len,
                    const int variant)
b64_maxlen = sodium_base64_encoded_len(strlen(str_bin), sodium_base64_VARIANT_ORIGINAL)
variant = sodium_base64_VARIANT_ORIGINAL or sodium_base64_VARIANT_ORIGINAL_NO_PADDING

    int sodium_base642bin(unsigned char * const bin, const size_t bin_maxlen,
                      const char * const b64, const size_t b64_len,
                      const char * const ignore, size_t * const bin_len,
                      const char ** const b64_end, const int variant);

*/

int main()
{
    if (sodium_init() == -1)
    {
        return 1;
    }

    const char *str_bin = "Hello World!";

    char *str_hex = (char *)malloc(strlen(str_bin) * 2 + 1); // allocate memory for str_hex
    str_hex = sodium_bin2hex(str_hex, strlen(str_bin) * 2 + 1, (const unsigned char *)str_bin, strlen(str_bin));
    cout << str_hex << endl;
    char *str_hex2bin = (char *)malloc(strlen(str_bin) + 1);
    sodium_hex2bin((unsigned char *)str_hex2bin, strlen(str_bin), str_hex, strlen(str_hex), NULL, NULL, NULL);
    cout << str_hex2bin << endl;

    char *str_b64 = sodium_bin2base64(str_b64, sodium_base64_encoded_len(strlen(str_bin), sodium_base64_VARIANT_ORIGINAL), (const unsigned char *)str_bin, strlen(str_bin), sodium_base64_VARIANT_ORIGINAL);
    cout << str_b64 << endl;
    char *str_b642bin = (char *)malloc(strlen(str_bin) + 1);
    sodium_base642bin((unsigned char *)str_b642bin, strlen(str_bin), str_b64, strlen(str_b64), NULL, NULL, NULL, sodium_base64_VARIANT_ORIGINAL);
    cout << str_b642bin << endl;

    return 0;
}
