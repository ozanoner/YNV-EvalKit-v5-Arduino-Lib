
#pragma once

#include "anim.h"
#include "disp_decimal_number.h"

namespace ynv
{
namespace anim
{

class Anim15SegSignedNegativeCounterDown : public Anim<ynv::ecd::DispSignedNumber>
{
   public:
    Anim15SegSignedNegativeCounterDown(ynv::ecd::DispSignedNumber& display) : Anim<ynv::ecd::DispSignedNumber>(display)
    {
    }

   protected:
    void transition() override
    {
        static int counter = 1;
        counter            = (counter + 1) % 100;          // Increment counter and wrap around at 100
        m_display.show(counter / 10, counter % 10, true);  // Update display with new values
    }
};

}  // namespace anim
}  // namespace ynv
