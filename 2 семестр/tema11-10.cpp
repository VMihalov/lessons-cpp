#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool isCharacterExist(char buffer, string bufferTwo);
void parseString(string f, string g, size_t fPos = 0, size_t gPos = 0);

int main() {
    fstream f, g;
    string bufferOne, bufferTwo;
    char buffer;
    int countOne = 0, countTwo = 0;


    f.open("f.txt");
    g.open("g.txt");

    if (!f.is_open() || !g.is_open()) {
        cerr << "Error opening files!\n";
        return 1;
    }
    vector <int> res;
    while (getline(f, bufferOne) && getline(g, bufferTwo)) {
        sort(bufferOne.begin(), bufferOne.end());
        sort(bufferTwo.begin(), bufferTwo.end());

        cout << "f: " << bufferOne << endl;
        cout << "g: " << bufferTwo << endl;

        int size = bufferOne.length() < bufferTwo.length() ? bufferOne.length() : bufferTwo.length();
        cout << "Little: " << size << endl;

        
    }

    for (auto i : res)
        cout << i << " | ";

    f.close();
    g.close();

    return 0;
}

void parseString(string f, string g, size_t fPos, size_t gPos) {
}

bool isCharacterExist(char buffer, string bufferTwo) {
    for (const auto v : bufferTwo)
        if (buffer == v)
            return true;

    return false;
}

