#include <iostream>
#include <time.h>

void renderMatrix(int** matrix, int col, int row);
int** sortMatrixByBiggerNumber(int** matrix, int col, int row);

int main()
{
    srand(time(NULL));

    int columns = 0, rows = 0;

    std::cout << "Columns: ";
    std::cin >> columns;
    std::cout << "Rows: ";
    std::cin >> rows;

    int** numbers = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        numbers[i] = new int[columns];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            numbers[i][j] = rand() % 10;
        }
    }

    renderMatrix(numbers, columns, rows);

    numbers = sortMatrixByBiggerNumber(numbers, columns, rows);

    std::cout << "\nSorted:\n";
    renderMatrix(numbers, columns, rows);

    for (int i = 0; i < rows; i++)
    {
        delete numbers[i];
    }

    delete[] numbers;

    return 1;
}

int** sortMatrixByBiggerNumber(int** matrix, int col, int row)
{
    int temporaryNumber = 0;
    int** sortMatrix = matrix;

    for (int a = 0; a < row; a++)
    {
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (sortMatrix[a][i] > sortMatrix[a][j])
                {
                    temporaryNumber = sortMatrix[a][i];
                    sortMatrix[a][i] = sortMatrix[a][j];
                    sortMatrix[a][j] = temporaryNumber;
                }
            }
        }
    }

    return sortMatrix;
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
