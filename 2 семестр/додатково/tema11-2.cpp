#include <iostream>
#include <string>

using namespace std;

bool isTrueForm(string formula);

int main() {
    string formula = "abcd12.";

    cout << isTrueForm(formula);

    return 0;
}

bool isTrueForm(string formula) {
    char next, prev;

    if (formula[0] == '.')
        if (formula.length() > 1) {
            std::cout << "Not\n";
            return false;
        } else {
            std::cout << "Yes\n";
            return true;
        }
    
    if (atoi(formula.substr(0, 1).c_str())) {
        if (formula[1] != '.')
            if (!atoi(formula.substr(1, 1).c_str())) {
                std::cout << "Not\n";
                return false;
            }
    }

    return isTrueForm(formula.substr(1));
}
