#include "catch_amalgamated.hpp"

#include "../trim_blanks.h"
#include "../trim_blanks.cpp"

SCENARIO("Тест TrimBlanks", "[trim_blanks]")
{
    GIVEN("Тест 1: Строка без пробелов по бокам")
    {
        std::string const input = "hello";
        THEN("Строка неизменна")
        {
            REQUIRE(TrimBlanks(input) == "hello");
        }
    }

    GIVEN("Тест 2: Пробелы только слева")
    {
        std::string const input = " hello";
        THEN("Пробелы слева удаляются")
        {
            REQUIRE(TrimBlanks(input) == "hello");
        }
    }

    GIVEN("Тест 3: Пробелы с обеих сторон")
    {
        std::string const input = " hello ";
        THEN("Пробелы с обеих сторон удаляются")
        {
            REQUIRE(TrimBlanks(input) == "hello");
        }
    }

    GIVEN("Тест 4: Пробелы только справа")
    {
        std::string const input = "hello   ";
        THEN("Пробелы справа удаляются")
        {
            REQUIRE(TrimBlanks(input) == "hello");
        }
    }

    GIVEN("Тест 5: Пробелы внутри строки")
    {
        std::string const input = "hello   world";
        THEN("Внутренние пробелы сохраняются, боковые удаляются")
        {
            REQUIRE(TrimBlanks(input) == "hello   world");
        }
    }

    GIVEN("Тест 6: Только пробелы")
    {
        std::string const input = "        ";
        THEN("Пустая строка")
        {
            REQUIRE(TrimBlanks(input) == "");
        }
    }

    GIVEN("Тест 7: Пустая строка")
    {
        std::string const input = "";
        THEN("Пустая строка")
        {
            REQUIRE(TrimBlanks(input) == "");
        }
    }

    GIVEN("Тест 8: Несколько строк")
    {
        std::string const line1 = "   first line  ";
        std::string const line2 = "     second line";

        THEN("Каждая строка обрабатывается")
        {
            REQUIRE(TrimBlanks(line1) == "first line");
            REQUIRE(TrimBlanks(line2) == "second line");
        }
    }

    GIVEN("Тест 9: Обработка знаков табуляции")
    {
        std::string const input = "\thello\t";
        THEN("Табуляция на концах строки удаляется")
        {
            REQUIRE(TrimBlanks(input) == "hello");
        }
    }

    GIVEN("Тест 10: Цифры и специальные символы")
    {
        std::string const input = "   123-abc #!   ";
        THEN("Символы и цифры остаются, пробелы по краям удаляются")
        {
            REQUIRE(TrimBlanks(input) == "123-abc #!");
        }
    }
}