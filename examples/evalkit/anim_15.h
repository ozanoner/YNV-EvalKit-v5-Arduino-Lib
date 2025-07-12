
#pragma once

#include "anim.h"
#include "disp_3seg_bar.h"

namespace ynv
{
namespace anim
{

class Anim3SegBarPos : public Anim<ynv::ecd::Disp3SegBar>
{
   public:
    Anim3SegBarPos(ynv::ecd::Disp3SegBar& display) : Anim<ynv::ecd::Disp3SegBar>(display) { }

   protected:
    void transition() override
    {
        int        pos[3] = {1, 0, 2};  // Positions for the 3 segments
        static int posIdx = 0;
        m_display.position(pos[posIdx]);  // Set the initial position
        posIdx = (posIdx + 1) % 3;        // Cycle through positions
    }
};

}  // namespace anim
}  // namespace ynv
