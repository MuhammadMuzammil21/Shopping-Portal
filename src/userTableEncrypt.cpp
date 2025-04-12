#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void encryptFile(string filename)
{
    ifstream inFile(filename, ios::in);
    string content;

    char ch;
    while (inFile.get(ch))
    {
        content += (ch + 5) % 256;
    }

    inFile.close();

    ofstream outFile(filename, ios::out | ios::binary);
    outFile << content;
    outFile.close();
}
void decryptFile(string filename)
{
    ifstream inFile(filename, ios::in | ios::binary);
    string content;

    char ch;
    while (inFile.get(ch))
        content += (int(ch) - 5 + 256) % 256;

    inFile.close();

    ofstream outFile(filename, ios::out | ios::binary);
    outFile.write(content.c_str(), content.size());
    outFile.close();
}

int main()
{
    // decryptFile("UserTable.dat");
    encryptFile("UserTable.dat");
}