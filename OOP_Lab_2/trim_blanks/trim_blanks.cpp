#include "trim_blanks.h"
#include <string>


std::string TrimBlanks(std::string const& str)
{
    const char* SEARCH_BLANKS = " \t";
    const size_t first = str.find_first_not_of(SEARCH_BLANKS);
    const size_t last = str.find_last_not_of(SEARCH_BLANKS);

    if (first == std::string::npos)
    {
        return "";
    }

  

    return str.substr(first, last - first + 1);
}