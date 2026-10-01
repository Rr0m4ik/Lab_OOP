#include "catch_amalgamated.hpp"
#include <sstream>

#include "../vector_proc.cpp"
#include "../vector_proc.h"

SCENARIO("Тест vector_proc", "[vector_proc]")
{
    GIVEN("Тест 1: Положительные числа")
    {
        std::stringstream input("1.0 2 3.659512");
        std::vector<double> numbers;

        REQUIRE(ReadNumbers(numbers, input));
        ProcessNumbers(numbers);

        THEN("Каждое число увеличивается на ср. арифметическое")
        {
            REQUIRE(numbers.size() == 3);
            REQUIRE(numbers[0] == Catch::Approx(3.220).epsilon(0.001));
            REQUIRE(numbers[1] == Catch::Approx(4.220).epsilon(0.001));
            REQUIRE(numbers[2] == Catch::Approx(5.879).epsilon(0.001));
        }
    }

    GIVEN("Тест 2: 1 отрицательное число")
    {
        std::stringstream input("4 16 -30 10");
        std::vector<double> numbers;

        REQUIRE(ReadNumbers(numbers, input));
        ProcessNumbers(numbers);
        std::sort(numbers.begin(), numbers.end()); 

        THEN("Отрицательное число не учитывается в ср. арифм., но тоже увеличивается")
        {
            REQUIRE(numbers[0] == Catch::Approx(-20.000));
            REQUIRE(numbers[1] == Catch::Approx(14.000));
            REQUIRE(numbers[2] == Catch::Approx(20.000));
            REQUIRE(numbers[3] == Catch::Approx(26.000));
        }
    }

    GIVEN("Тест 3: Только отрицательные числа")
    {
        std::stringstream input("-1.0004000 -703 -3.659512 -11");
        std::vector<double> numbers;

        REQUIRE(ReadNumbers(numbers, input));
        ProcessNumbers(numbers);
        std::sort(numbers.begin(), numbers.end());

        THEN("Среднее не вычисляется, числа остаются неизменными и сортируются")
        {
            REQUIRE(numbers[0] == Catch::Approx(-703.000));
            REQUIRE(numbers[1] == Catch::Approx(-11.000));
            REQUIRE(numbers[2] == Catch::Approx(-3.660).epsilon(0.001));
            REQUIRE(numbers[3] == Catch::Approx(-1.000).epsilon(0.001));
        }
    }

    GIVEN("Тест 4: Некорректный начальный символ")
    {
        std::stringstream input("- 2 3");
        std::vector<double> numbers;

        THEN("Ошибка ввода")
        {
            REQUIRE_FALSE(ReadNumbers(numbers, input));
        }
    }

    GIVEN("Тест 5: Пустой ввод")
    {
        std::stringstream input("");
        std::vector<double> numbers;

        THEN("Пустой вывод")
        {
            REQUIRE(ReadNumbers(numbers, input));
            REQUIRE(numbers.empty());
        }
    }

    GIVEN("Тест 6: Текст в середине ввода")
    {
        std::stringstream input("1.5 abc 3.4");
        std::vector<double> numbers;

        THEN("ReadNumbers падает с ошибкой")
        {
            REQUIRE_FALSE(ReadNumbers(numbers, input));
        }
    }

    GIVEN("Тест 7: Многострочный ввод с разделителями")
    {
        std::stringstream input("2.0\n4.0\t6.0");
        std::vector<double> numbers;

        REQUIRE(ReadNumbers(numbers, input));
        ProcessNumbers(numbers);
        std::sort(numbers.begin(), numbers.end());

        THEN("Корректный вывод")
        {
            REQUIRE(numbers[0] == Catch::Approx(6.000));
            REQUIRE(numbers[1] == Catch::Approx(8.000));
            REQUIRE(numbers[2] == Catch::Approx(10.000));
        }
    }

    GIVEN("Тест 8: Обработка ровно 1 положительного числа")
    {
        std::stringstream input("5.5");
        std::vector<double> numbers;

        REQUIRE(ReadNumbers(numbers, input));
        ProcessNumbers(numbers);

        THEN("Число прибавляет само себя")
        {
            REQUIRE(numbers[0] == Catch::Approx(11.000));
        }
    }

    GIVEN("Тест 9: Ввод с 0")
    {
        std::stringstream input("0 2 4");
        std::vector<double> numbers;

        REQUIRE(ReadNumbers(numbers, input));
        ProcessNumbers(numbers);
        std::sort(numbers.begin(), numbers.end());

        THEN("Ноль не положительное число, при расчете среднего не учитывается")
        {
            REQUIRE(numbers[0] == Catch::Approx(3.000));
            REQUIRE(numbers[1] == Catch::Approx(5.000));
            REQUIRE(numbers[2] == Catch::Approx(7.000));
        }
    }

    GIVEN("Тест 10: Много пробелов между числами")
    {
        std::stringstream input("   10.0       20.0   ");
        std::vector<double> numbers;

        REQUIRE(ReadNumbers(numbers, input));
        ProcessNumbers(numbers);
        std::sort(numbers.begin(), numbers.end());

        THEN("Лишние пробелы успешно игнорируются")
        {
            REQUIRE(numbers[0] == Catch::Approx(25.000));
            REQUIRE(numbers[1] == Catch::Approx(35.000));
        }
    }
}
