#include <iostream>
#include <cstdint>

int size = 0;
char space;
char symbol;

template <typename T>
void upTriangle(T** arr)
{
    for (int i = 0; i < ::size; i++)
    {
        for (int j = i; j < ::size - i; j++)
        {
            arr[i][j] = ::symbol;
        }
        
    }
    

}

template <typename T>
void downTriangle(T** arr)
{   
    int step = 0;

    for (int i = ::size / 2; i < ::size; i++)
    {
        for (int j = ::size - i; j < i; j++)
        {
            arr[i][j] = ::symbol;
        }

        step++;
    }
    
}

template <typename T>
void rightTriangle(T** arr)
{
    int step = 0;

    for (int i = 0; i < ::size; i++)
    {
        // step = i < ::size/2 ? step += 1 : step -= 1;
        step = i < ::size/2 ? step += 1 : step -= 1;

        if (::size % 2 == 0 &&  i < ::size/2)
            step++;
        
        for (int j = ::size; j >= ::size - step; j--)
        {
            arr[i][j] = ::symbol;
        }
    }
}

template <typename T>
void leftTriangle(T** arr)
{
    for (int i = 0; i < ::size; i++)
    {
        int step = i < ::size/2 ? i : size - i;

        for (int j = 0; j < step; j++)
        {
            arr[i][j] = ::symbol;
        }
        
        
    }
}

int main()
{
    int orientation;
    bool error = false;

    std::cout << "Size\n> ";
    std::cin >> ::size;

    std::cout << "Space\n> ";
    std::cin >> ::space;

    std::cout << "Triangle\n> ";
    std::cin >> ::symbol;

    while (true)
    {
        std::cout << "\n1 - Up 2 - Down 3 - Left 4 - Right\n> ";
        std::cin >> orientation;

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
        default:
            std::cout << "Invalid number!" << std::endl;
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