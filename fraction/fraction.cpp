#include <iostream>

int size = 1;

struct fraction
{
    int numerator;
    int denominator;
};

int gcd(fraction* den)
{
    int res = 1;
    bool error = false;

    while (true)
    {
        error = false;

        for (int i = 0; i < ::size; i++)
        {
            if (res % den[i].denominator != 0) {
                error = true;
            }

        }
        
        if (error) 
            res++;
        else
            break;
    }
    
    return res;
}

fraction sum(fraction* numbers) {
    int sum = 0;
    int nod = 0;
    fraction result;

    nod = gcd(numbers);

    for (int i = 0; i < ::size; i++)
    {
        sum += (nod / numbers[i].denominator) * numbers[i].numerator;
    }

    return result = { sum, nod };
}

fraction subtraction(fraction* numbers) {
    int substraction = 0;
    int nod = 0;
    fraction result;

    nod = gcd(numbers);

    substraction = (nod / numbers[0].denominator) * numbers[0].numerator;

    for (int i = 1; i < ::size; i++)
    {
        substraction -= (nod / numbers[i].denominator) * numbers[i].numerator;
    }

    return result = { substraction, nod };
}

fraction multiplication(fraction* numbers) {
    int num = 1;
    int den = 1;
    fraction result;

    for (int i = 0; i < ::size; i++)
    {
        num *= numbers[i].numerator;
        den *= numbers[i].denominator;
    }

    return result = { num, den };  
}

fraction division(fraction* numbers) {
    int num = numbers[0].numerator;
    int den = numbers[0].denominator;
    fraction result;

    for (int i = 1; i < ::size; i++)
    {
        num *= numbers[i].denominator;
        den *= numbers[i].numerator;
    }
    
    return result = { num, den };
}

int main() {
    fraction out;
    char operation = '+';

    std::cout << "Number of fractions: ";
    std::cin >> ::size;

    fraction* darr = new fraction[::size];
    
    std::cout << "Input numerator and denominator with space "<< ::size << " times\n" ;

    for (int i = 0;i < ::size; i++) {
        std::cin >> darr[i].numerator;
        std::cin >> darr[i].denominator;
    }
    
    std::cout << "Insert operation + - / *\n> ";
    std::cin >> operation;

    if (::size > 1) {
        switch (operation)
        {
        case '+':
            out = sum(darr);
            break;
        case '-':
            out = subtraction(darr);
            break;
        case '/':
            out = division(darr);
            break;
        case '*':
            out = multiplication(darr);
            break;
        default:
            break;
        }
    } else {
        out = { darr[0].numerator, darr[0].denominator };
    }

    std::cout << "Result: " << out.numerator << "/" << out.denominator << std::endl;

    delete[] darr;
}