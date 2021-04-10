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
vector <Book> sortBooksByYear(vector <Book> books);

int main() {
    vector <Book> books;

    books = readFile("library.txt");
    books = sortBooksByYear(books);

    for (auto v : books)
        cout << v.title << " | " << v.author << " | " << v.year << endl;

    return 0;
}

vector <Book> sortBooksByYear(vector <Book> books) {
    for (int i = 0; i < books.size(); i++) {
        for (int j = 0; j < books.size(); j++) {
            if (books[i].year < books[j].year) {
                Book tmp = books[i];
                books[i] = books[j];
                books[j] = tmp;
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
