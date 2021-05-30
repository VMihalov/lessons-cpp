#include <iostream>
#include <time.h>
#define RANGE 100

using namespace std;

void generateMatrix(int** &matrix, int &x, int &y);
void fillRandom(int** &matrix, int &x, int &y);
void deleteMatrix(int** &matrix, int x, int y);
void orderMatrix(int** &matrix, int x, int y);
void renderMatrix(int** matrix, int col, int row);
int getMaxNumber(int* arr, int length);

int main()
{
    srand(time(NULL));

    int x, y;
    int** matrix;
    
    generateMatrix(matrix, x, y);

    fillRandom(matrix, x, y);

    cout << "Your matrix:" << endl;
    renderMatrix(matrix, x, y);

    orderMatrix(matrix, x, y);

    cout << endl << "Ordered matrix:" << endl;
    renderMatrix(matrix, x, y);

    deleteMatrix(matrix, x, y);

    return 1;
}

void generateMatrix(int** &matrix, int &x, int &y) {
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;

    matrix = new int*[y];

    for (int i = 0; i < y; i++)
        matrix[i] = new int[x];
}

void fillRandom(int** &matrix, int &x, int &y) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            matrix[i][j] = rand() % RANGE;
        }
    }
}

void orderMatrix(int** &matrix, int x, int y) {
    int buffer = getMaxNumber(matrix[0], x);
    int current;
    int* tmp;

    for (int i = 0; i < y; i++) {
        buffer = getMaxNumber(matrix[i], x);

        for (int j = 0; j < y; j++) {
            current = getMaxNumber(matrix[j], x);

            if (current > buffer) {
                tmp = matrix[i];
                matrix[i] = matrix[j];
                matrix[j] = tmp;
            }
        }
    }
}

void deleteMatrix(int** &matrix, int x, int y) {
    for (int i = 0; i < y; i++)
        delete matrix[i];

    delete matrix;
}

void renderMatrix(int** matrix, int col, int row)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

int getMaxNumber(int* arr, int length) {
    int max = 0;

    for (int i = 0; i < length; i++) {
        if (arr[i] > max) max = arr[i];
    }

    return max;
}
