//Лабораторная 2, задание 2, вариант 1.

#include "trim_blanks.h"
#include <iostream>
#include <string>

int main()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::cout << TrimBlanks(line) << "\n";
    }

    return 0;
}