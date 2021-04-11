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

vector <Book> readFile(string fileName);
vector <Book> sortByYearAndAlphabet(vector <Book> books);
void push(string fileName, vector <Book> books);

int main() {
    string fileName = "library.txt";
    vector <Book> books;

    books = readFile(fileName);
    books = sortByYearAndAlphabet(books);
    push(fileName, books);

    return 0;
}

vector <Book> sortByYearAndAlphabet(vector <Book> books) {
    for (int i = 0; i < books.size(); i++) {
        for (int j = 0; j < books.size(); j++) {
            if (books[i].year < books[j].year) {
                Book tmp = books[i];
                books[i] = books[j];
                books[j] = tmp;
            }

            if (books[i].year == books[j].year) {
                if(books[i].author < books[j].author) {
                    Book tmp = books[i];
                    books[i] = books[j];
                    books[j] = tmp;
                }
            }
        }
    }

    return books;
}

vector <Book> readFile(string fileName) {
    fstream file;
    string field;

    vector <string> tmp;
    vector <Book> books;
    
    file.open(fileName);

    if (!file.is_open()) {
        throw "Error opening file!";
    }

    while (getline(file, field))
    {
        string str = "";
        size_t pos = 0;
        tmp.clear();
        while ((pos = field.find(";")) != std::string::npos) {
            str = field.substr(0, pos);
            tmp.push_back(str);
            field.erase(0, pos + 1);
        }

        Book book;
        book.title = tmp[0];
        book.author = tmp[1];
        book.year = stoi(tmp[2]);
        books.push_back(book);
    }
    
    file.close();

    return books;
}

void push(string fileName, vector <Book> books) {
    fstream file;

    file.open(fileName);

    if (!file.is_open())
        throw "Error opening file!\n";

    file.clear();

    for (const auto book: books) {
        file << book.title << ";" << book.author << ";" << book.year << ";\n";
    }

    file.close();
}
