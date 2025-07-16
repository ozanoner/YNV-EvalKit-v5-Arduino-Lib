
#pragma once

#include "ecd.h"

namespace ynv
{
namespace ecd
{
class DispSingleSegment : public ECD<1>
{
   public:
    using ECD<1>::ECD;  // Inherit constructors from ECD<1>

    void on()
    {
        m_nextStates[0] = true;  // Set the single segment to color state
    }

    void off()
    {
        m_nextStates[0] = false;  // Set the single segment to bleach state
    }
};
}  // namespace ecd
}  // namespace ynv