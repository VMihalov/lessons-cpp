#include <cctype> 
#include <iostream>
#include <string>

using namespace std;

bool check(const string formula);
bool readFormula(const string &formula, size_t &pos);
bool readTerm(const string &formula, size_t &pos);
bool readName(const string &formula, size_t &pos);
bool readNumber(const string &formula, size_t &pos);
bool readLetter(const string &formula, size_t &pos);
bool readDigit(const string &formula, size_t &pos);
bool readMark(const string &formula, size_t &pos, char symbol);
bool isValidCharacter(char symbol);
bool isEnd(const string &formula, size_t &pos);

int main() {
    string formula[] = {
        "abcde.",
        "a+b+100.",
        "ab+bc*a1.",
        "a234-b."
        "f0.",
        ".a.",
        ".",
        ""
    };

    for (const auto v : formula)
        cout << "Formula " << v << (check(v) ? " correct\n" : " incorrect\n");

    return 0;
}

bool check(const string formula) {
    size_t pos = 0;

    return (readFormula(formula, pos) && isEnd(formula, pos));
}

bool readFormula(const string &formula, size_t &pos) {
    bool result = readTerm(formula, pos);

    if (formula[pos] == '+' || formula[pos] == '-' || formula[pos] == '*') {
        pos++;
        result = result && readFormula(formula, pos);
    }

    return result;
}

bool readTerm(const string &formula, size_t &pos) {
    if (isalpha(formula[pos])) {
        return readName(formula, pos);
    }
    else if (isdigit(formula[pos])) {
        return readNumber(formula, pos);
    }

    return false;
}

bool readName(const string &formula, size_t &pos) {
    if (!isValidCharacter(formula[pos])) {
        ++pos;
        return false;
    }

    while(isValidCharacter(formula[pos])) {
        readLetter(formula, pos);
    }

    if (isdigit(formula[pos])) {
        pos++;
        if (isdigit(formula[pos]))
            return false;
    }

    return true;
}

bool readLetter(const string &formula, size_t &pos) {
    if (!isalpha(formula[pos]))
        return false;

    ++pos;

    return true;
}

bool readNumber(const string &formula, size_t &pos) {
    if (!readDigit(formula, pos))
        return false;

    while (isdigit(formula[pos])) {
        readDigit(formula, pos);
    }

    if (isalpha(formula[pos]))
        return false;

    return true;
}

bool readDigit(const string &formula, size_t &pos) {
    if (!isdigit(formula[pos]))
        return false;

    ++pos;

    return true;
}

bool readMark(const string &formula, size_t &pos, char symbol) {
    if (formula[pos] != symbol)
        return false;

    ++pos;

    return true;
}

bool isValidCharacter(char symbol) {
    char letters[] = {'a', 'b', 'c', 'd', 'e'};
    bool isValid = false;

    if (!isalpha(symbol))
        return false;
    
    for (const auto v : letters)
        if (v == symbol)
            isValid = true;

    return isValid;
}

bool isEnd(const string &formula, size_t &pos) {
    if (readMark(formula, pos, '.')) {
        if (formula[pos] == 0)
            return true;
    }

    return false;
}
