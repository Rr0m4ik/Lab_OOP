//Лабораторная 1, задание 2, вариант 1

#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <cstdint>

const char* const MSG_INVALID_ARG = "Invalid argument\n";
const char* const MSG_HELP = "Usage: calcbits.exe <byte>\nCalculates the number of set bits (1s) in a byte.\nOptions:\n  -h  Show this help message\n";

int CountSetBits(uint8_t byte)
{
    int count = 0;
    while (byte > 0)
    {
        if ((byte & 1) == 1) 
        {
            count++;
        }
        byte >>= 1; 
    }
    return count;
}

bool TryParseByte(const std::string& str, uint8_t& outByte)
{
    if (str.empty()) return false;

    for (char c : str)
    {
        if (c < '0' || c > '9') return false;
    }

    try
    {
        size_t processedChars = 0;
        long long val = std::stoll(str, &processedChars);

        if (processedChars != str.length() || val < 0 || val > 255)
        {
            return false;
        }

        outByte = static_cast<uint8_t>(val);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

int main(int argc, char* argv[])
{
    constexpr int MODE_STDIN = 1;
    constexpr int MODE_ARG = 2;

    if (argc == MODE_STDIN)
    {
        std::string inputStr;
        if (!(std::cin >> inputStr))
        {
            std::cout << MSG_INVALID_ARG;
            return 0; 
        }

        uint8_t byteValue = 0;
        if (!TryParseByte(inputStr, byteValue))
        {
            std::cout << MSG_INVALID_ARG;
            return 0; 
        }

        std::cout << CountSetBits(byteValue) << "\n";
        return 0;
    }

    if (argc == MODE_ARG)
    {
        std::string arg = argv[1];

        if (arg == "-h")
        {
            std::cout << MSG_HELP;
            return 0;
        }

        uint8_t byteValue = 0;
        if (!TryParseByte(arg, byteValue))
        {
            std::cout << MSG_INVALID_ARG;
            return 1; 
        }

        std::cout << CountSetBits(byteValue) << "\n";
        return 0;
    }

    std::cout << MSG_INVALID_ARG;
    return 1;
}