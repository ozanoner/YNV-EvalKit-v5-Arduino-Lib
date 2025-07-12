
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
};

using DispSignedNumber = DispDecimalNumber;  // Alias for signed number display

}  // namespace ecd
}  // namespace ynv