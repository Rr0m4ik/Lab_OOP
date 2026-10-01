#include "catch_amalgamated.hpp"
#include "../tvset/CTVSet.h"
#include "../tvset/CTVSetControl.h"

#include "../tvset/CTVSet.cpp"
#include "../tvset/CTVSetControl.cpp"

#include <sstream>

SCENARIO("Базовые команды класса CTVSetControl", "[control]") 
{
    GIVEN("Потоки ввода-вывода") 
    {
        CTVSet tv;
        std::stringstream input;
        std::stringstream output;
        WHEN("команда TurnOn") 
        {
            input << "TurnOn\n";
            CTVSetControl::RunCommandProcessing(tv, input, output);
            THEN("включается") 
            {
                REQUIRE(tv.IsTurnedOn());
                REQUIRE(output.str() == MSG_TV_ON);
            }
        }

        WHEN("Info для выключенного ТВ") 
        {
            input << "Info\n";
            CTVSetControl::RunCommandProcessing(tv, input, output);
            THEN("ТВ выключен") 
            {
                REQUIRE(output.str() == MSG_TV_OFF);
            }
        }
    }
}

SCENARIO("Граничные значения и ошибки через CTVSetControl", "[control]") 
{
    GIVEN("Включенный телевизор") 
    {
        CTVSet tv;
        std::stringstream input;
        std::stringstream output;
        tv.TurnOn();

        WHEN("Минимальный корректный канал") 
        {
            input << "SelectChannel 1\n";
            CTVSetControl::RunCommandProcessing(tv, input, output);

            THEN("Канал переключён на 1") 
            {
                REQUIRE(tv.GetChannel() == 1);
                REQUIRE(output.str() == "Channel switched to: 1\n");
            }
        }

        WHEN("Максимальный корректный канал") 
        {
            input << "SelectChannel 99\n";
            CTVSetControl::RunCommandProcessing(tv, input, output);

            THEN("Канал переключён на 99") 
            {
                REQUIRE(tv.GetChannel() == 99);
                REQUIRE(output.str() == "Channel switched to: 99\n");
            }
        }

        WHEN("Канал за нижней границей") 
        {
            input << "SelectChannel 0\n";
            CTVSetControl::RunCommandProcessing(tv, input, output);

            THEN("Канал остается прежним") 
            {
                REQUIRE(tv.GetChannel() == 1);
                REQUIRE(output.str() == MSG_ERROR);
            }
        }

        WHEN("Канал за верхней границей") 
        {
            input << "SelectChannel 100\n";
            CTVSetControl::RunCommandProcessing(tv, input, output);

            THEN("Канал остается прежним") 
            {
                REQUIRE(tv.GetChannel() == 1);
                REQUIRE(output.str() == MSG_ERROR);
            }
        }

        WHEN("Неизвестная синтаксическая команда") 
        {
            input << "ChangeVolume 10\n";
            CTVSetControl::RunCommandProcessing(tv, input, output);

            THEN("Выводится сообщение о неизвестной команде") 
            {
                REQUIRE(output.str() == MSG_ERROR);
            }
        }
    }
}

SCENARIO("Цепочки команд и сохранения памяти", "[control]") 
{
    GIVEN("Обработка потока") 
    {
        CTVSet tv;
        std::stringstream input;
        std::stringstream output;

        WHEN("Включить -> Канал 45 -> Выключить -> Инфо") 
        {
            input << "TurnOn\n";
            input << "SelectChannel 45\n";
            input << "TurnOff\n";
            input << "Info\n";

            CTVSetControl::RunCommandProcessing(tv, input, output);

            THEN("Телевизор выключен, сохранен канал 45") 
            {
                REQUIRE_FALSE(tv.IsTurnedOn());
                tv.TurnOn();
                REQUIRE(tv.GetChannel() == 45);
                tv.TurnOff();
                REQUIRE_FALSE(tv.IsTurnedOn());
                tv.TurnOn();
                REQUIRE(tv.GetChannel() == 45);
            }
        }
    }
}