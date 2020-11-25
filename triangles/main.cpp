#include <iostream>

using namespace std;

int x = 10;
int y = 10;
char space = ' ';
char symbol;

void upTriangle(string t[::y][::x]) {
    int a = 0, b = ::x;

    for (int i = ::y/2; i < ::y; i++) {
        for (int c = 0; c < ::x; c++) {
            if (c >= a && c < b) {
                t[i][c] = symbol;
            } else {
                t[i][c] =  space;
            }
        }
        a++;
        b--;

        cout << endl;
    }

}

void downTriangle() {
    int a = ::x/2, b = ::x/2;

    for (int i = 0; i < ::y; i++) {
        for (int c = 0; c < ::x; c++) {
            if (c >= a && c <= b) cout << symbol;
            else cout << space;
        }
        a--;
        b++;
        cout << endl;
    }

}

void leftTriangle() {
    int a = ::x/2, b;

    for (int i = 0; i <= ::y; i++) {
        for (int c = 0; c < ::x; c++) {
            if (c < a || c > ::x/2) cout << space;
            else cout << symbol;
        }

        if (i < ::y/2) a--;
        else a++;

        cout << endl;

    }

}

void rightTriangle() {
    int a = ::x/2, b;

    for (int i = 0; i <= ::y; i++) {
        for (int c = 0; c < ::x; c++) {
            if (c < a && c >= ::x/2 - 1) cout << symbol;
            else cout << space;
        }

        if (i < ::y/2) a++;
        else a--;

        cout << endl;
    }
}

int main() {
    int width, height, orientation;
    char space, triangle;
    char arr[::y][::x];

//    for (int y = 0; y < ::y; y++) {
//        for (int x = 0; x < ::x; x++) {
//            arr[y][x] = '-';
//        }
//    }

    while (true) {

        cout << "Input width: ";
        cin >> ::x;

        cout << "Input height: ";
        cin >> ::y;

        cout << "Space: ";
        cin >> ::space;

        cout << "Triangle: ";
        cin >> ::symbol;

        cout << "Orientation: 1 - Up 2 - Down 3 - Left 4 - Right \n Type: ";
        cin >> orientation;


        switch (orientation) {
            case 1:
                upTriangle(arr[::y][::x]);
                break;
            case 2:
                downTriangle();
                break;
            case 3:
                leftTriangle();
                break;
            case 4:
                rightTriangle();
                break;
        }

        cout << "Show array: \n";

        for (int y = 0; y < ::y; y++) {
            for (int x = 0; x < ::x; x++) {
                cout << arr[y][x];
            }
            cout << endl;
        }

    }
    return 0;
}
