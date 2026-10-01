// Лабораторная 3, задание 1, вариант 1 (3-1-1)
#include <iostream>
#include "CTVSet.h"
#include "CTVSetControl.h"

int main()
{
    CTVSet tv;
    CTVSetControl::RunCommandProcessing(tv, std::cin, std::cout);
    return 0;
}