#include "CTVSetControl.h"
#include <string>
#include <sstream>
#include <map>
#include <functional>

void CTVSetControl::RunCommandProcessing(CTVSet& tv, std::istream& input, std::ostream& output)
{
    std::map<std::string, std::function<void(std::stringstream&)>> commandMap;
    commandMap[CMD_TURN_ON] = [&tv, &output](std::stringstream&)
        {
            if (tv.TurnOn())
            {
                output << MSG_TV_ON;
            }
        };

    commandMap[CMD_TURN_OFF] = [&tv, &output](std::stringstream&)
        {
            if (tv.TurnOff())
            {
                output << MSG_TV_OFF;
            }
        };

    commandMap[CMD_SELECT_CHANNEL] = [&tv, &output](std::stringstream& ss)
        {
            int channel = 0;
            if (ss >> channel)
            {
                if (tv.SelectChannel(channel))
                {
                    output << MSG_SWITCH_PREFIX << tv.GetChannel() << "\n";
                }
                else
                {
                    output << MSG_ERROR;
                }
            }
        };

    commandMap[CMD_INFO] = [&tv, &output](std::stringstream&)
        {
            if (tv.IsTurnedOn())
            {
                output << MSG_TV_ON << MSG_CHANNEL_PREFIX << tv.GetChannel() << "\n";
            }
            else
            {
                output << MSG_TV_OFF;
            }
        };

    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        auto it = commandMap.find(command);
        if (it != commandMap.end())
        {
            it->second(ss);
        }
        else
        {
            output << MSG_ERROR;
        }
    }
}