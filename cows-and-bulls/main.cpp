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
            if (res[j] == (char)number) 
                error = true;
        }

        if (!error) {
            res += to_string(number);
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
            if (first[i] == second[j] && i == j)
                a++;
            if (first[i] == second[j]) b++;
        }
    }

    return result = {a, b};
}

int main()
{
    string bot = randNumber();
    string user = "";

    while (bot.compare(user) != 0) {
        cout << "Insert number: ";
        cin >> user;

        Check check = checkNumbers(bot, user);

        if (check.error) {
            cout << "Try again!\n";

            continue;
        }

        cout << check.cows << "/" << check.bulls << endl;
    }

    cout << "You win!" << endl;

    return 0;
}