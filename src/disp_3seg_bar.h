
#pragma once

#include "ecd.h"

namespace ynv
{
namespace ecd
{
class Disp3SegBar : public ECD<3>
{
   public:
    using ECD<3>::ECD;  // Inherit constructors from ECD<3>

    // Function to toggle the state of the segments
    void increment()
    {
        ++m_pos;
        updateNextStatesIncDec();
    }

    void decrement()
    {
        --m_pos;
        updateNextStatesIncDec();
    }

    void position(int pos)
    {
        m_pos = pos % 3;  // Ensure position is within bounds
        for (int i = 0; i < 3; ++i)
        {
            m_nextStates[i] = (i == m_pos);  // Set segments based on position
        }
    }

    int getPos() const { return m_pos; }

   private:
    int m_pos = 0;

    void updateNextStatesIncDec()
    {
        m_pos %= 3;  // Wrap around if exceeds segment count
        for (int i = 0; i < m_pos; ++i)
        {
            m_nextStates[i] = true;  // Set segments to color state
        }
        for (int i = m_pos; i < 3; ++i)
        {
            m_nextStates[i] = false;  // Set remaining segments to bleach state
        }
    }
};
}  // namespace ecd
}  // namespace ynv