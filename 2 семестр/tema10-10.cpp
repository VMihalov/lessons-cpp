#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define TRIMSIZE 5

using namespace std;

int main() {
    const string fileTitle = "./numbers.txt";
    const string newFileTitle = "./sortedNumbers.txt";
    int* numbers = new int[TRIMSIZE];
    int count = 0;
    int buffer = 0;
    fstream fileOne, fileTwo;

    fileOne.open(fileTitle);
    fileTwo.open(newFileTitle, ios::out | ios::trunc);

    while (!fileOne.eof()) {
        fileOne >> buffer;

        if (count < TRIMSIZE) {
            numbers[count] = buffer;
            count++;
        } else {
            fileTwo << buffer << " "; 
        }
    }

    for (int i = 0; i < TRIMSIZE; i++)
        fileTwo << numbers[i] << " ";

    fileOne.close();
    fileTwo.close();

    return 0;
}