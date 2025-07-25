
#pragma once

#include "anim.h"
#include "disp_single_segment.h"

namespace ynv
{
namespace anim
{

class Anim1SegOn : public Anim<ynv::ecd::DispSingleSegment>
{
   public:
    Anim1SegOn(std::shared_ptr<ynv::ecd::DispSingleSegment> display) : Anim<ynv::ecd::DispSingleSegment>(display) { }

   protected:
    void transition() override
    {
        m_display->toggle();  // Toggle the display state
    }
};

}  // namespace anim
}  // namespace ynv
