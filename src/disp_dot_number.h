
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
};
}  // namespace ecd
}  // namespace ynv