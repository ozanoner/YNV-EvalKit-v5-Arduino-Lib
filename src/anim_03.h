
#pragma once

#include "anim.h"
#include "disp_decimal_number.h"

namespace ynv
{
namespace anim
{

class Anim15SegSignedPositiveCounterDown : public Anim<ynv::ecd::DispSignedNumber>
{
   public:
    Anim15SegSignedPositiveCounterDown(ynv::ecd::DispSignedNumber& display) : Anim<ynv::ecd::DispSignedNumber>(display)
    {
    }

   protected:
    void transition() override
    {
        static int counter = 99;
        counter            = (counter - 1) % 100;           // Decrement counter and wrap around at 100
        m_display.show(counter / 10, counter % 10, false);  // Update display with new values
    }
};

}  // namespace anim
}  // namespace ynv
