#include <cryptopp/base64.h>
#include <cryptopp/hex.h>
#include <cryptopp/rsa.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/randpool.h>
#include <cryptopp/validate.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/seckey.h>
#include <cryptopp/cryptlib.h>

#include <iostream>

int main(int argc, char *argv[])
{

    using namespace CryptoPP;

    // unsigned char *key = (unsigned char *)"01234567890123456789012345678901";
    // unsigned char *iv = (unsigned char *)"0123456789012345";
    // size_t key_size = strlen((const char *)key);

    // if (argc != 3)
    // {
    //     fprintf(stdout, "Usage: %s <plaintext file> <encrypt file>\n", argv[0]);
    //     fprintf(stdout, "Example: %s my_text_msg.txt my_encrypt_msg.txt\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    // CBC_Mode<AES>::Encryption encryptor(key, key_size, iv);
    // std::cout << "Algorithm Name: " << encryptor.AlgorithmName() << std::endl;
    // std::cout << "Default Key Length: " << encryptor.DefaultKeyLength() << std::endl;
    // std::cout << "Key Size: " << key_size << std::endl;
    // std::cout << "Maximum Key Length: " << encryptor.MaxKeyLength() << std::endl;
    // std::cout << "Minimum Key Length: " << encryptor.MinKeyLength() << std::endl;
    // std::cout << "IV size: " << encryptor.IVSize() << std::endl;
    // std::cout << "Maximum IV Length: " << encryptor.MaxIVLength() << std::endl;
    // std::cout << "Minimum IV Length: " << encryptor.MinIVLength() << std::endl;

    // FileSource(argv[1], true, new StreamTransformationFilter(encryptor, new FileSink(argv[2])));

    return 0;
}
