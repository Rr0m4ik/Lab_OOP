#pragma once

class CTVSet
{
public:
    CTVSet();

    bool IsTurnedOn() const;
    int GetChannel() const;

    bool TurnOn();
    bool TurnOff();
    bool SelectChannel(int channel);

private:
    static constexpr int MIN_CHANNEL = 1;
    static constexpr int MAX_CHANNEL = 99;
    static constexpr int DEFAULT_CHANNEL = 1;
    static constexpr int OFF_CHANNEL = 0;

    bool m_isOn;
    int m_currentChannel;
};