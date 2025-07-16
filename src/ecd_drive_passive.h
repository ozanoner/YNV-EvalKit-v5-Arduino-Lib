
#pragma once

#include <array>

#include "ecd_drive_base.h"

namespace ynv
{
namespace ecd
{
template <int SEGMENT_COUNT>
class ECDDrivePassive : public ECDDriveBase<SEGMENT_COUNT>
{
   public:
    ~ECDDrivePassive() = default;

    using ECDDriveBase<SEGMENT_COUNT>::ECDDriveBase;  // Inherit constructors
    using ECDDriveBase<SEGMENT_COUNT>::m_pins;
    using ECDDriveBase<SEGMENT_COUNT>::m_config;
    using ECDDriveBase<SEGMENT_COUNT>::enableCounterElectrode;
    using ECDDriveBase<SEGMENT_COUNT>::disableCounterElectrode;

    void drive(std::array<bool, SEGMENT_COUNT>&       currentStates,
               const std::array<bool, SEGMENT_COUNT>& nextStates) override
    {
        enableCounterElectrode(512);
        for (int i = 0; i < SEGMENT_COUNT; ++i)
        {
            pinMode(m_pins[i], OUTPUT);
            if (nextStates[i])
            {
                digitalWrite(m_pins[i], HIGH);
            }
            else
            {
                digitalWrite(m_pins[i], LOW);
            }
            currentStates[i] = nextStates[i];
        }
        delay(50);  // Allow time for the segments to stabilize
        for (int i = 0; i < SEGMENT_COUNT; ++i)
        {
            pinMode(m_pins[i], INPUT);  // Set the segment pins to input to disable them
        }
        disableCounterElectrode();
    }
};
}  // namespace ecd
}  // namespace ynv