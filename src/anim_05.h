
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
    Anim15SegSignedNegativeCounterDown(std::shared_ptr<ynv::ecd::DispSignedNumber> display)
        : Anim<ynv::ecd::DispSignedNumber>(display)
    {
    }

   protected:
    void transition() override
    {
        static int counter = 1;
        m_display->show(counter / 10, counter % 10, true);  // Update display with new values
        if (++counter == 100)
        {
            counter = 1;
        }
    }
};

}  // namespace anim
}  // namespace ynv
