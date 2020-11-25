#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

string randNumber() {
    srand(time(0));
    string res = "0000";

    for (int i = 0; i < 4;) {
        int error = 0;
        int number = rand() % 10;

        for (int j = 0; j < i; j++) {
            if (res[j] == number + '0') error++;
        }

        if (error == 0) {
            res[i] = number + '0';
            i++;
        }
    }

    return res;
}

string checkNumbers(string first, string second) {
    int a = 0, b = 0;
    string result = "";

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (first[i] == second[j] && i == j) a++;
            if (first[i] == second[j]) b++;
        }
    }

    result += a + '0';
    result += b + '0';

    return result;
}

int main()
{
    string comp = randNumber();
    string you = "";

    while (true) {
        cout << "Insert number: ";
        cin >> you;

        string check = checkNumbers(comp, you);

        cout << check[0] << "/" << check[1] << endl;
        if (check[0] == '4' && check[1] == '4') break;
    }

    cout << "You win!" << endl;

    return 0;
}
