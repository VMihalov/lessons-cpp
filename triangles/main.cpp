#include <iostream>
#include <limits>

int size = 0;
char space = ' ';
char symbol;

void upTriangle(char** arr)
{
    int a = 0, b = ::size;

    for (int i = 0; i < ::size; i++)
    {
        for (int c = 0; c < ::size; c++)
        {
            if (c >= a && c < b)
            {
                arr[i][c] = ::symbol;
            }
        }
        a++;
        b--;
    }

}

void downTriangle(char** arr)
{
    int a = ::size % 2 == 0 ? size / 2 - 1 : size / 2;
    int b = ::size % 2 == 0 ? a + 1 : a;


    for (int i = 0; i < ::size; i++)
    {
        for (int j = 0; j < ::size; j++)
        {
            if (j >= a && j <= b && i >= ::size / 2)
            {
                arr[i][j] = ::symbol;
            }
        }
        if (i >= ::size / 2)
        {
            a--;
            b++;
        }
    }

}

void rightTriangle(char** arr)
{
    int a = ::size - 1;
    int isEven = ::size % 2 == 0 ? 1 : 0;

    for (int i = 0; i < ::size; i++)
    {
        for (int j = 0; j < ::size; j++)
        {
            if (j >= a)
            {
                arr[i][j] = ::symbol;
            }
            
        }

        if (i < (::size / 2) - isEven) a--;
        else a++;

        if (i == (::size / 2) - 1 && isEven == 1) a--;
    }

}

void leftTriangle(char** arr)
{
    int a = 0;
    int isEven = ::size % 2 == 0 ? 1 : 0;

    for (int i = 0; i < ::size; i++)
    {
        for (int j = 0; j < ::size; j++)
        {
            if (j <= a)
            {
                arr[i][j] = ::symbol;
            }
            else
            {
                arr[i][j] = ::space;
            }
        }

        if (i < (::size / 2) - isEven) a++;
        else if (i > (::size / 2) - isEven) a--;

        if (i == ::size / 2 && isEven == 0) a--;

        std::cout << std::endl;
    }
}

void insertNumber(int& var, int start, int stop)
{
    while (true)
    {
        std::cout << "\n> ";
        std::cin >> var;

        if (std::cin.good())
        {
            if (var < start || var > stop)
            {
                std::cout << "\nNumber must be from " << start << " to " << stop << std::endl;
                goto error;
            }

            break;
        }

        if (std::cin.fail())
        {
        error:
            std::cerr << "Try again!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }
    }
}

void insertChar(char& var)
{
    while (true)
    {
        std::cout << "\n> ";
        std::cin >> var;

        if (std::cin.good())
        {
            if (std::cin.get() != 10)
            {
                std::cout << "Only 1 symbol!";
                goto error;
            }

            break;
        }

        if (std::cin.fail())
        {
        error:

            std::cout << "\nTry again!";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main()
{
    int orientation;

    while (true)
    {
        std::cout << "Size";
        insertNumber(::size, 1, 100);

        std::cout << "\nSpace";
        insertChar(::space);

        std::cout << "\nTriangle";
        insertChar(::symbol);

        std::cout << "\n1 - Up 2 - Down 3 - Left 4 - Right";
        insertNumber(orientation, 1, 4);

        
        char im[22][22];
        char** image = new char*[::size];

        for (int i = 0; i < ::size; i++)
        {
            image[i] = new char[::size];
        }

        for (int y = 0; y < ::size; y++)
        {
            for (int x = 0; x < ::size; x++)
            {
                image[y][x] = ::space;
            }
        }

        
        switch (orientation)
        {
        case 1:
            upTriangle(image);
            break;
        case 2:
            downTriangle(image);
            break;
        case 3:
            leftTriangle(image);
            break;
        case 4:
            rightTriangle(image);
            break;
        }
        
        std::cout << "\nYour triangle: \n\n";

        for (int y = 0; y < ::size; y++)
        {
            for (int x = 0; x < ::size; x++)
            {
                std::cout << image[y][x];
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

        for (int i = 0; i < ::size; i++)
        {
            delete []image[i];
        }
    }

    return 0;
}
