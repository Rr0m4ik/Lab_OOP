#pragma once
#include <iostream>
#include <string>
#include <sstream>

const char* const MSG_TV_ON = "TV is turned on\n";
const char* const MSG_TV_OFF = "TV is turned off\n";
const char* const MSG_CHANNEL_PREFIX = "Channel is: ";
const char* const MSG_SWITCH_PREFIX = "Channel switched to: ";
const char* const MSG_ERROR = "ERROR\n";

class CTVSet
{
public:
    CTVSet() : m_isOn(false), m_currentChannel(1) {}

    bool IsTurnedOn() const { return m_isOn; }
    int GetChannel() const { return m_isOn ? m_currentChannel : 0; }

    bool TurnOn()
    {
        if (m_isOn) return false;
        m_isOn = true;
        return true;
    }

    bool TurnOff()
    {
        if (!m_isOn) return false;
        m_isOn = false;
        return true;
    }

    bool SelectChannel(int channel)
    {
        if (!m_isOn || channel < MIN_CHANNEL || channel > MAX_CHANNEL)
        {
            return false;
        }
        m_currentChannel = channel;
        return true;
    }

private:
    static constexpr int MIN_CHANNEL = 1;
    static constexpr int MAX_CHANNEL = 99;

    bool m_isOn;
    int m_currentChannel;
};

class CTVSetControl
{
public:
    static void RunCommandProcessing(CTVSet& tv, std::istream& input, std::ostream& output)
    {
        std::string line;
        while (std::getline(input, line))
        {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string command;
            ss >> command;

            if (command == "TurnOn")
            {
                if (tv.TurnOn()) output << MSG_TV_ON;
            }
            else if (command == "TurnOff")
            {
                if (tv.TurnOff()) output << MSG_TV_OFF;
            }
            else if (command == "SelectChannel")
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
            }
            else if (command == "Info")
            {
                if (tv.IsTurnedOn())
                {
                    output << MSG_TV_ON << MSG_CHANNEL_PREFIX << tv.GetChannel() << "\n";
                }
                else
                {
                    output << MSG_TV_OFF;
                }
            }
            else
            {
                output << MSG_ERROR;
            }
        }
    }
};