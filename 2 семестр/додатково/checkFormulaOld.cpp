#include <iostream>
#include <string>

using namespace std;

bool isTrueForm(string formula);
bool isMark(string symbol);
bool isNumber(string symbol);
bool isLetter(string symbol);
string getPrev(string formula, string symbol);
string getSymbol(string text);

int main() {
    string formula = "a+b1.";

    //std::cout << "Insert formula: ";
    //getline(cin, formula);

    if (isTrueForm(formula))
        cout << "This is the correct formula!\n";
    else
        cout << "This is the wrong formula!\n";

    return 0;
}

bool isTrueForm(string formula) {
    static string fullFormula = formula;
    string cur, next, prev;

    cur = getSymbol(formula);

    if (cur.empty())
        return false;

    if (cur == " ")
        return false;

    if (cur == ".") {
        next = getSymbol(formula.substr(1));

        if (next.empty()) {
            return true;
        }

        return false;
    } 
    else if (isNumber(cur)) {
        next = getSymbol(formula.substr(1));

        //if (!isNumber(next))

        if (!isMark(next))
                return false;
    } 
    else if (isMark(cur)) {
        prev = getPrev(fullFormula, cur);
        next = getSymbol(formula.substr(1));

        cout << prev;
        if (prev.empty())
            return false;

        if (next == ".")
            return false;

        if (isMark(next))
            return false;
    }
    else if (!isLetter(cur)) {
        return false;
    }

    return isTrueForm(formula.substr(1));
}

bool isNumber(string symbol) {
    bool correct = true;

    try {
        stoi(symbol);
    } catch(...) {
        correct = false;
    } 

    return correct;
}

bool isMark(string symbol) {
    if (symbol == "." || symbol == "+" || symbol == "-" || symbol == "*") {
        return true;
    }

    return false;
}

bool isLetter(string symbol) {
    string arr[5] = {"a", "b", "c", "d", "e"};

    for (int i = 0; i < 5; i++) {
        if (symbol == arr[i])
            return true;
    }

    return false;
}

string getPrev(string formula, string symbol) {
    size_t pos = formula.find(symbol);

    if (pos == 0)
        return {};
    else
        return formula.substr(pos - 1, 1);

    return symbol;
}

string getSymbol(string text) {
    return text.substr(0, 1);
}
