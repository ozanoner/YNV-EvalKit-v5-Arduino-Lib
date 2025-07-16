
#pragma once

#include "anim.h"
#include "disp_7seg_bar.h"

namespace ynv
{
namespace anim
{

class Anim7SegBarCounterDown : public Anim<ynv::ecd::Disp7SegBar>
{
   public:
    Anim7SegBarCounterDown(ynv::ecd::Disp7SegBar& display) : Anim<ynv::ecd::Disp7SegBar>(display) { }

   protected:
    void transition() override
    {
        m_display.decrement();  // Decrement the bar display
    }
};

}  // namespace anim
}  // namespace ynv
