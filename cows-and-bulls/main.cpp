#include <iostream>
#include <stdlib.h>
#include <time.h>
#define SIZE 4

using namespace std;

struct Check {
    int cows = 0;
    int bulls = 0;
    bool error = false;
};

string randNumber() {
    srand(time(0));
    string res = "";

    for (int i = 0; i < SIZE;) {
        int error = false;
        int number = rand() % 10;

        for (int j = 0; j < i; j++) {
            if (res[j] == number + '0') 
                error = true;
        }

        if (!error) {
            res += number + '0';
            i++;
        }
    }

    return res;
}

Check checkNumbers(string first, string second) {
    int a = 0, b = 0;
    Check result;

    if (first.length() != SIZE || second.length() != SIZE) {
        result.error = true;

        return result;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (first[i] == second[j] && i == j) a++;
            if (first[i] == second[j]) b++;
        }
    }

    return result = {a, b};
}

int main()
{
    string comp = randNumber();
    string you = "";

    while (comp.compare(you) != 0) {
        cout << "Insert number: ";
        cin >> you;

        Check check = checkNumbers(comp, you);

        if (check.error) {
            cout << "Try again!\n";

            continue;
        }

        cout << check.cows << "/" << check.bulls << endl;
    }

    cout << "You win!" << endl;

    return 0;
}
