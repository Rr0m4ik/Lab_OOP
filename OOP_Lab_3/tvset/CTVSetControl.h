#pragma once
#include <iostream>
#include "CTVSet.h"

static const std::string CMD_TURN_ON = "TurnOn";
static const std::string CMD_TURN_OFF = "TurnOff";
static const std::string CMD_SELECT_CHANNEL = "SelectChannel";
static const std::string CMD_INFO = "Info";

static const std::string MSG_TV_ON = "TV is turned on\n";
static const std::string MSG_TV_OFF = "TV is turned off\n";
static const std::string MSG_CHANNEL_PREFIX = "Channel is: ";
static const std::string MSG_SWITCH_PREFIX = "Channel switched to: ";
static const std::string MSG_ERROR = "ERROR\n";

class CTVSetControl
{
public:
    static void RunCommandProcessing(CTVSet& tv, std::istream& input, std::ostream& output);
};