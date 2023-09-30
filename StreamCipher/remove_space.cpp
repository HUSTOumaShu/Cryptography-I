#include <iostream>
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

int main()
{
    string type;
    while (type != "c")
    {
        getline(cin, type);
        if (type == "c")
            break;
        cout << remove_space(type) << endl;
    }
}
