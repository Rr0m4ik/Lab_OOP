//Лабораторная 1, задание 1, вариант 1

#include <iostream>
#include <fstream>
#include <string>

const char* const MSG_INVALID_ARGS = "Invalid arguments count\n";
const char* const MSG_READ_OPEN_FAILED = "Failed to open input file for reading\n";
const char* const MSG_WRITE_OPEN_FAILED = "Failed to open output file for writing\n";
const char* const MSG_READ_FAILED = "Failed to read data from input file\n";
const char* const MSG_WRITE_FAILED = "Failed to save data on disk\n";
const char* const MSG_SAME_FILES = "Error: Input and output file paths are identical\n";

int main(int argc, char* argv[])
{
    constexpr int EXPECTED_ARG_COUNT = 3;

    if (argc != EXPECTED_ARG_COUNT)
    {
        std::cerr << MSG_INVALID_ARGS;
        return 1;
    }

    if (std::string(argv[1]) == std::string(argv[2]))
    {
        std::cerr << MSG_SAME_FILES;
        return 1;
    }

    std::ifstream input(argv[1], std::ios::binary);
    if (!input.is_open())
    {
        std::cerr << MSG_READ_OPEN_FAILED;
        return 1;
    }

    std::ofstream output(argv[2], std::ios::binary);
    if (!output.is_open())
    {
        std::cerr << MSG_WRITE_OPEN_FAILED;
        return 1;
    }

    char ch;
    while (input.get(ch))
    {
        if (!output.put(ch))
        {
            std::cerr << MSG_WRITE_FAILED;
            return 1;
        }
    }

    if (input.bad())
    {
        std::cerr << MSG_READ_FAILED;
        return 1;
    }

    if (!output.flush())
    {
        std::cerr << MSG_WRITE_FAILED;
        return 1;
    }

    return 0;
}