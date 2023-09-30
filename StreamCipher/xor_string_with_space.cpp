#include <iostream>
#include <assert.h>
#include <vector>
#include <string.h>
using namespace std;

string remove_space(string str)
{
    string result = "";
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
        {
            result += str[i];
        }
    }
    return result;
}

string add_space(string str)
{
    string result = "";
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (i % 2 == 0 && i != 0)
        {
            result += " ";
        }
        result += str[i];
    }
    return result;
}

static inline unsigned int value(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

string str_xor(string const &s1, string const &s2)
{
    int delta_length = s1.length() - s2.length();
    delta_length = delta_length > 0 ? delta_length : -delta_length;

    string hex1, hex2;
    if (s1.length() > s2.length())
    {
        hex1 = s1;
        hex2 = string(delta_length, '0') + s2;
    }
    else if (s1.length() < s2.length())
    {
        hex1 = string(delta_length, '0') + s1;
        hex2 = s2;
    }
    else
    {
        hex1 = s1;
        hex2 = s2;
    }

    static char const alphabet[] = "0123456789abcdef";

    string result;
    result.reserve(hex1.length());

    for (size_t i = 0; i != hex1.length(); i++)
    {
        unsigned int v = value(hex1[i]) ^ value(hex2[i]);
        assert(v < sizeof(alphabet)); // or other error handling
        result.push_back(alphabet[v]);
    }
    return result;
}

int main()
{
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);
    cout << "String after XOR:" << endl;
    str1 = remove_space(str1);
    str2 = remove_space(str2);
    string str = str_xor(str1, str2);
    cout << str << endl;
    // cout << add_space(str) << endl;
}
