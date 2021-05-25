#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define TRIMSIZE 5

using namespace std;

int main() {
    const string fileTitle = "./доделал/numbers.txt";
    const string newFileTitle = "sortedNumbers.txt";
    int* numbers = new int[TRIMSIZE];
    int count = 0;
    int buffer = 0;
    fstream file;

    file.open(fileTitle);

    while (!file.eof()) {
        file >> buffer;

        if (count < TRIMSIZE) {
            numbers[count] = buffer;
            count++;
        } else {
            cout << buffer << " ";    
        }
    }

    for (int i = 0; i < TRIMSIZE; i++)
        cout << numbers[i] << " ";

    file.close();

    return 0;
}