#include <cctype> 
#include <iostream>
#include <string>

using namespace std;

bool check(const string formula);
bool passFormula(const string &formula, size_t &pos);
bool passTerm(const string &formula, size_t &pos);
bool passName(const string &formula, size_t &pos);
bool passWord(const string &formula, size_t &pos);
bool passNumber(const string &formula, size_t &pos);
bool passDigit(const string &formula, size_t &pos);
bool passMark(const string &formula, size_t &pos, char symbol);
bool isEnd(const string &formula, size_t &pos);

int main() {
    string formula = "a*c.";

    cout << check(formula);

    return 0;
}

bool check(const string formula) {
    size_t pos = 0;

    return (passFormula(formula, pos) && isEnd(formula, pos));
}

bool passFormula(const string &formula, size_t &pos) {
    bool result = passTerm(formula, pos);

    if (formula[pos] == '+' || formula[pos] == '-' || formula[pos] == '*') {
        pos++;
        result = result && passFormula(formula, pos);
    }

    return result;
}

bool passTerm(const string &formula, size_t &pos) {
    if (isalpha(formula[pos])) {
        return passName(formula, pos);
    }
    else if (isdigit(formula[pos])) {
        return passNumber(formula, pos);
    }

    return false;
}

bool passName(const string &formula, size_t &pos) {
    if (!passWord(formula, pos))
        return false;

    while(isalpha(formula[pos])) {
        passWord(formula, pos);
    }

    if (isdigit(formula[pos])) {
        pos++;
        if (isdigit(formula[pos]))
            return false;
    }

    return true;
}

bool passWord(const string &formula, size_t &pos) {
    if (!isalpha(formula[pos]))
        return false;
 
    ++pos;
    return true;
}

bool passNumber(const string &formula, size_t &pos) {
    if (!passDigit(formula, pos))
        return false;

    while (isdigit(formula[pos])) {
        passDigit(formula, pos);
    }

    if (isalpha(formula[pos]))
        return false;

    return true;
}

bool passDigit(const string &formula, size_t &pos) {
    if (!isdigit(formula[pos]))
        return false;

    ++pos;

    return true;
}

bool passMark(const string &formula, size_t &pos, char symbol) {
    if (formula[pos] != symbol)
        return false;

    ++pos;

    return true;
}

bool isEnd(const string &formula, size_t &pos) {
    if (passMark(formula, pos, '.')) {
        if (formula[pos] == 0)
            return true;
    }

    return false;
}
