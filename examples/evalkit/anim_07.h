
#pragma once

#include "anim.h"
#include "disp_decimal_number.h"

namespace ynv
{
namespace anim
{

class Anim15SegDecimalCounterDown : public Anim<ynv::ecd::DispDecimalNumber>
{
   public:
    Anim15SegDecimalCounterDown(ynv::ecd::DispDecimalNumber& display) : Anim<ynv::ecd::DispDecimalNumber>(display) { }

   protected:
    void transition() override
    {
        static int counter = 0;
        counter            = (counter - 1) % 100;    // Increment counter and wrap around at 100
        m_display.show(counter / 10, counter % 10);  // Update display with new values
    }
};

}  // namespace anim
}  // namespace ynv
