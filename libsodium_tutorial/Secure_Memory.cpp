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
    unsigned char buf[buf_len] = {0x01, 0x02, 0x03, 0x04, 0x05,
                                  0x06, 0x07, 0x08, 0x09, 0x0A};
    print(buf, buf_len);
    sodium_memzero(buf, buf_len); // overwrite the memory with zeros

    sodium_mlock(buf, buf_len);   // lock the allocation in memory
    sodium_munlock(buf, buf_len); // unlock the allocation in memory

    print(buf, buf_len);

    unsigned char *new_buf = (unsigned char *)sodium_malloc(buf_len);               // allocate memory
    unsigned char **new_arr_buf = (unsigned char **)sodium_allocarray(10, buf_len); // allocate memory for an array of pointers

    sodium_mprotect_noaccess(new_buf);  // set the memory to no access
    sodium_mprotect_readonly(new_buf);  // set the memory to read only
    sodium_mprotect_readwrite(new_buf); // set the memory to read write

    sodium_free(new_arr_buf); // free the allocated memory
    sodium_free(new_buf);     // free the allocated memory

    return 0;
}
