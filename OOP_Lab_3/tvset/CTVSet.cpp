#include "CTVSet.h"

CTVSet::CTVSet()
    : m_isOn(false)
    , m_currentChannel(DEFAULT_CHANNEL)
{
}

bool CTVSet::IsTurnedOn() const
{
    return m_isOn;
}

int CTVSet::GetChannel() const
{
    if (m_isOn)
    {
        return m_currentChannel;
    }
    return OFF_CHANNEL;
}

bool CTVSet::TurnOn()
{
    if (m_isOn)
    {
        return false;
    }
    m_isOn = true;
    return true;
}

bool CTVSet::TurnOff()
{
    if (!m_isOn)
    {
        return false;
    }
    m_isOn = false;
    return true;
}

bool CTVSet::SelectChannel(int channel)
{
    if (!m_isOn || channel < MIN_CHANNEL || channel > MAX_CHANNEL)
    {
        return false;
    }
    m_currentChannel = channel;
    return true;
}