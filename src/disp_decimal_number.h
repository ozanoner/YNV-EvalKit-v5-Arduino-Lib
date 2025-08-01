
#pragma once

#include <Arduino.h>

#include "ecd.h"

namespace ynv
{
namespace ecd
{
class DispDecimalNumber : public ECD<15>
{
   public:
    using ECD<15>::ECD;  // Inherit constructors from ECD<15>

    void show(uint8_t number1, uint8_t number2, bool dotOrMinus = true)
    {
        number1 %= 10;                 // Ensure number is within 0-9
        number2 %= 10;                 // Ensure number is within 0-9
        m_nextStates[0] = dotOrMinus;  // Set the dotOrMinus state
        for (int i = 0; i < 7; ++i)
        {
            m_nextStates[i + 1] = bitRead(numberMask()[number1], i);
            m_nextStates[i + 8] = bitRead(numberMask()[number2], i);
        }
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
        m_config.refreshColorLimitHVoltage  = (int)(m_config.maxAnalogValue * 0.85f);
        m_config.refreshColorLimitLVoltage  = (int)(m_config.maxAnalogValue * 0.7f);
        m_config.refreshBleachingVoltage    = (int)(m_config.maxAnalogValue / 2 * 0.6f);
        m_config.refreshBleachPulseTime     = 50;
        m_config.refreshBleachLimitHVoltage = (int)(m_config.maxAnalogValue * 0.4f);
        m_config.refreshBleachLimitLVoltage = (int)(m_config.maxAnalogValue * 0.3f);
    }
};

using DispSignedNumber = DispDecimalNumber;  // Alias for signed number display

}  // namespace ecd
}  // namespace ynv