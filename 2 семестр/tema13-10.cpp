#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Book {
    string title;
    string author;
    int year;
};

void readFile(string fileName, vector <Book> &arr);
void sortByYearAndAlphabet(vector <Book> &arr);
void writeFile(string fileName, vector <Book> arr);

int main() {
    try {
        string fileName = "library.txt";
        vector <Book> books;

        readFile(fileName, books);

        sortByYearAndAlphabet(books);

        writeFile(fileName, books);
    } catch(const char* error) {
        cerr << error << endl;
    }

    return 0;
}

void sortByYearAndAlphabet(vector <Book> &arr) {
    Book tmp;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (arr[i].year < arr[j].year) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }

            if (arr[i].year == arr[j].year) {
                if(arr[i].author < arr[j].author) {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
}

void readFile(string fileName, vector <Book> &arr) {
    ifstream file(fileName);
    Book tmp;

    if (!file.is_open()) throw "Error opening file";

    while (!file.eof()) {
        file >> tmp.author;
        file >> tmp.title;
        file >> tmp.year;

        arr.push_back(tmp);
    }
    
    file.close();
}

void writeFile(string fileName, vector <Book> arr) {
    ofstream file;

    file.open(fileName, ios::trunc);

    if (!file.is_open()) throw "Error opening file";

    file.clear();

    for (int i = 0; i < arr.size(); i++) {
        file << arr[i].author << " " << arr[i].title << " " << arr[i].year;

        if (i != arr.size() - 1) file << endl;
    }

    file.close();
}
