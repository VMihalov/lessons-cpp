#include <iostream>
#include <stdint.h>

int size = 1;

struct Fraction
{
    int numerator;
    int denominator;
};

int gcd(Fraction* den)
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

Fraction cut(Fraction fraction) {
    Fraction num = fraction;
    bool error = false;

    for (int i = 2; i < 9; i++)
    {
        error = false;

        while (true)
        {
            if (num.numerator % i != 0 || num.denominator % i != 0) {
                error = true;
            }

            if (error) break;

            num.numerator = num.numerator / i;
            num.denominator = num.denominator / i;
        }   
    }

    return num;
}

Fraction sum(Fraction* numbers) {
    int sum = 0;
    int nod = 0;
    Fraction result;

    nod = gcd(numbers);

    for (int i = 0; i < ::size; i++)
    {
        sum += (nod / numbers[i].denominator) * numbers[i].numerator;
    }

    return result = { sum, nod };
}

Fraction subtraction(Fraction* numbers) {
    int substraction = 0;
    int nod = 0;
    Fraction result;

    nod = gcd(numbers);

    substraction = (nod / numbers[0].denominator) * numbers[0].numerator;

    for (int i = 1; i < ::size; i++)
    {
        substraction -= (nod / numbers[i].denominator) * numbers[i].numerator;
    }

    return result = { substraction, nod };
}

Fraction multiplication(Fraction* numbers) {
    int num = 1;
    int den = 1;
    Fraction result;

    for (int i = 0; i < ::size; i++)
    {
        num *= numbers[i].numerator;
        den *= numbers[i].denominator;
    }

    return result = { num, den };  
}

Fraction division(Fraction* numbers) {
    int num = numbers[0].numerator;
    int den = numbers[0].denominator;
    Fraction result;

    for (int i = 1; i < ::size; i++)
    {
        num *= numbers[i].denominator;
        den *= numbers[i].numerator;
    }
    
    return result = { num, den };
}

int main() {
    bool error = false;
    Fraction out;
    char operation = '+';

    std::cout << "Number of fractions: ";
    std::cin >> ::size;

    Fraction* darr = new Fraction[::size];
    
    std::cout << "Input numerator and denominator with space "<< ::size << " times\n" ;

    for (int i = 0;i < ::size; i++) {
        std::cin >> darr[i].numerator;
        std::cin >> darr[i].denominator;
    }
    
    std::cout << "Insert operation + - / *\n> ";
    std::cin >> operation;

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
        error = true;
        break;
    }
    
    out = cut(out);

    if (!error)
        std::cout << "Result: " << out.numerator << "/" << out.denominator << std::endl;   
    else
        std::cout << "Error" << std::endl;

    delete[] darr;

    return 1;
}