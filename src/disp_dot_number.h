
#pragma once

#include <Arduino.h>

#include "ecd.h"

namespace ynv
{
namespace ecd
{
class DispDotNumber : public ECD<8>
{
   public:
    using ECD<8>::ECD;  // Inherit constructors from ECD<8>

    void show(uint8_t number, bool dot = true)
    {
        number %= 10;  // Ensure number is within 0-9
        for (int i = 0; i < 7; ++i)
        {
            m_nextStates[i] = bitRead(numberMask()[number], i);
        }
        m_nextStates[7] = dot;  // Set the dot state
    }

   protected:
    void initConfig() override
    {
        m_config.coloringVoltage            = (int)(m_config.maxAnalogValue / 2);
        m_config.coloringTime               = 500;
        m_config.bleachingVoltage           = (int)(m_config.maxAnalogValue / 2 * 0.8f);
        m_config.bleachingTime              = 500;
        m_config.refreshColoringVoltage     = (int)(m_config.maxAnalogValue / 2 * 0.8f);
        m_config.refreshColorPulseTime      = 50;
        m_config.refreshColorLimitHVoltage  = (int)(m_config.maxAnalogValue * 0.8f);
        m_config.refreshColorLimitLVoltage  = (int)(m_config.maxAnalogValue * 0.6f);
        m_config.refreshBleachingVoltage    = (int)(m_config.maxAnalogValue / 2 * 0.6f);
        m_config.refreshBleachPulseTime     = 50;
        m_config.refreshBleachLimitHVoltage = (int)(m_config.maxAnalogValue * 0.4f);
        m_config.refreshBleachLimitLVoltage = (int)(m_config.maxAnalogValue * 0.3f);
    }
};
}  // namespace ecd
}  // namespace ynv