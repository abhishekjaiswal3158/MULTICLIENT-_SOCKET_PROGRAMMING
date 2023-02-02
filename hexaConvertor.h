#include<string>
using namespace std;

string hexToASCII(string &hex)
{
    string ascii = "";
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        string part = hex.substr(i, 2);
        char ch = stoul(part, nullptr, 16);
        ascii += ch;
    }
    return ascii;
}

string decToHexa(int n)
{

    char hexaDeciNum[100];
    int i = 0;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        n = n / 16;
    }
 
    string ans = "";
    for (int j = i - 1; j >= 0; j--)
        ans += hexaDeciNum[j];
 
    return ans;
}

string ASCIItoHEX(string &ascii)
{
    string hex = "";
    for (int i = 0; i < ascii.length(); i++) {
        char ch = ascii[i];
        int tmp = (int)ch;
        string part = decToHexa(tmp);
        hex += part;
    }
    return hex;
}