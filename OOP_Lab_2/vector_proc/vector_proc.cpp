//Лабораторная 2, задание 1, вариант 1

#include "vector_proc.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <string>
#include <iterator>

bool ReadNumbers(std::vector<double>& numbers, std::istream& input)
{
    double val;
    while (input >> val)
    {
        numbers.push_back(val);
    }

    if (!input.eof())
    {
        return false;
    }
    return true;
}

void ProcessNumbers(std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return;
    }

    auto isPositive = [](double x) { return x > 0.0; };
    long long positiveCount = std::count_if(numbers.begin(), numbers.end(), isPositive);

    if (positiveCount == 0)
    {
        return;
    }

    double positiveSum = std::accumulate(numbers.begin(), numbers.end(), 0.0, [](double sum, double x) {
        return x > 0.0 ? sum + x : sum;
        });

    double average = positiveSum / static_cast<double>(positiveCount);

    for (double& x : numbers)
    {
        x += average;
    }
}

void PrintSortedNumbers(const std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return;
    }

    constexpr int PRECISION_DIGITS = 3;
    std::vector<double> copyToSort = numbers;
    std::sort(copyToSort.begin(), copyToSort.end());
    std::cout << std::fixed << std::setprecision(PRECISION_DIGITS);

    std::copy(copyToSort.begin(), copyToSort.end(), std::ostream_iterator<double>(std::cout, " "));

    std::cout << "\n";
}