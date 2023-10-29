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

    size_t buf_len = 10;
    size_t padded_len;
    size_t block_size = 16;
    size_t max_len = 100;
    unsigned char buf[max_len] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

    sodium_pad(&padded_len, buf, buf_len, block_size, max_len);
    print(buf, padded_len);

    sodium_unpad(&padded_len, buf, padded_len, block_size);
    print(buf, padded_len);
    return 0;
}
