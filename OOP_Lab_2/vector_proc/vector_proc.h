#pragma once
#include <vector>
#include <iostream>

bool ReadNumbers(std::vector<double>& numbers, std::istream& input = std::cin);

void ProcessNumbers(std::vector<double>& numbers);

void PrintSortedNumbers(const std::vector<double>& numbers);