
#pragma once

#include "ecd.h"

namespace ynv
{
namespace ecd
{
class Disp7SegBar : public ECD<7>
{
   public:
    using ECD<7>::ECD;  // Inherit constructors from ECD<7>

    // Function to toggle the state of the segments
    void increment()
    {
        ++m_pos;
        updateNextStates();
    }

    void decrement()
    {
        --m_pos;
        updateNextStates();
    }

    void resetPos() { m_pos = 0; }
    int  getPos() const { return m_pos; }

   private:
    int m_pos = 0;

    void updateNextStates()
    {
        m_pos %= 7;  // Wrap around if exceeds segment count
        for (int i = 0; i < m_pos; ++i)
        {
            m_nextStates[i] = true;  // Set segments to color state
        }
        for (int i = m_pos; i < 7; ++i)
        {
            m_nextStates[i] = false;  // Set remaining segments to bleach state
        }
    }
};
}  // namespace ecd
}  // namespace ynv