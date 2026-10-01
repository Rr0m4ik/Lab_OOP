#include <iostream>
#include <vector>
#include <string>

int main()
{
    const std::string MSG_ERROR = "ERROR\n";
    std::vector<double> numbers;

    if (!ReadNumbers(numbers, std::cin))
    {
        std::cout << MSG_ERROR;
        return 0;
    }
    ProcessNumbers(numbers);
    PrintSortedNumbers(numbers);

    return 0;
}