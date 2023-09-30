#include <iostream>
#include <assert.h>
using namespace std;

string hex_to_string(string const &hex)
{
    assert(hex.length() % 2 == 0);
    string result;
    result.reserve(hex.length() / 2);
    for (unsigned int i = 0; i < hex.length(); i += 2)
    {
        int v = (hex[i] - '0') * 16 + (hex[i + 1] - '0');
        result.push_back(v);
    }
    return result;
}

int main()
{
    string str;
    getline(cin, str);
    cout << hex_to_string(str) << endl;
}

// 09e1c5f70a65ac519458e7e53f36
// 6895b196690e8c30e07883844858
