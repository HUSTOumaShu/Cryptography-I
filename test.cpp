#include <sodium.h>

#include <iostream>
#include <sodium.h>

int main(void)
{
    if (sodium_init() == -1)
    {
        return 1;
    }
    return 0;
}
