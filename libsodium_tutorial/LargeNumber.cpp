#include <iostream>
#include <sodium.h>
#include <string.h>
using namespace std;

// Incrementing large numbers
/*
    void sodium_increment(unsigned char *n, const size_t nlen)
can be used to increment nonces in constant time
*/

// Adding/Subtracting large numbers
/*
    void sodium_add(unsigned char *a, const unsigned char *b, const size_t len)
(a + b) mod 2^(8*len) and return a
    void sodium_sub(unsigned char *a, const unsigned char *b, const size_t len)
(a - b) mod 2^(8*len) and return a
*/

// Comparing large numbers
/*
    int sodium_compare(const unsigned char *b1_, const unsigned char *b2_, const size_t len)
return -1 if b1_ < b2_
return 0 if b1_ = b2_
return 1 if b1_ > b2_
*/

// Testing for all zeros
/*
    int sodium_is_zero(const unsigned char *n, const size_t nlen)
return 1 if n is all zeros
*/

// Clearing the stack
/*
    void sodium_memzero(void * const pnt, const size_t len)
*/

int main()
{
    if (sodium_init() == -1)
    {
        return 1;
    }
    unsigned char a[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    unsigned char b[16] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
    sodium_add((unsigned char *)a, (const unsigned char *)b, sizeof(a));
    for (int i = 0; i < sizeof(a); i++)
    {
        printf("%02X ", a[i]);
    }
    return 0;
}
