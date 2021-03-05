#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define TRIMSIZE 5

int main() {
    const std::string fileTitle = "numbers.txt";
    const std::string newFileTitle = "sortedNumbers.txt";
    std::vector<std::string> numbers;
    std::fstream file;

    file.open(fileTitle);

    std::string text;
    while (getline(file, text, ',')){
        numbers.push_back(text);
    }

    file.close();

    file.open(newFileTitle, std::fstream::out | std::fstream::trunc);

    std::string tmp = "";
    for (int i = 0; i < TRIMSIZE; i++) {
        numbers.push_back(numbers[0]);
        numbers.erase(numbers.begin());
    }
    
    file << numbers[0];
    numbers.erase(numbers.begin());
    for(auto var : numbers) {
        file << "," << var;
    }

    file.close();

    return 0;
}