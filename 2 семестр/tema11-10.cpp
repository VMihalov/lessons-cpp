#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int binarySearch(string arr, char elem);

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

        char buffer = bufferTwo[0];
        char oldBuffer;
        int pos;
        int i = 0;
        while (i < bufferTwo.length()) {
            buffer = bufferTwo[i];
            if (buffer == oldBuffer) {
                i++;
                continue;
            }
            pos = binarySearch(bufferOne, buffer);
            if (pos != -1) {
                bufferOne.erase(pos, pos + 1);
                pos = binarySearch(bufferOne, buffer);
                if (pos != -1) {
                    cout << buffer << " | ";
                }
            }   else {
                cout << buffer << " | ";
            }
            oldBuffer = bufferTwo[i];
            i++;
        }
        
    }

    f.close();
    g.close();

    return 0;
}

int binarySearch(string arr, char elem) {
    int start = 0;
    int end = arr.length();
    bool find = false;
    int pos = -1;

    while (find == false && start <= end) {
        int mid = (start + end) / 2;
        if (arr[mid] == elem) {
            find = true;
            pos = mid;
        }

        if (elem < arr[mid]) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    
    return pos;
}
