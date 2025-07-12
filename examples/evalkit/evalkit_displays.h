#pragma once

#include <Arduino.h>

#include <array>

#include "disp_3seg_bar.h"
#include "disp_7seg_bar.h"
#include "disp_decimal_number.h"
#include "disp_dot_number.h"
#include "disp_single_segment.h"
#include "ecd.h"

namespace ynv
{
namespace ecd
{

template <>
inline ECD<1>::ECD(const std::array<int, 1>& pins)
    : m_pins(pins), m_states({}), m_nextStates({}), m_config(getConfigDefaults())
{
    m_config.coloringTime               = 700;
    m_config.bleachingTime              = 800;
    m_config.refreshColoringVoltage     = 1.4;
    m_config.refreshColorPulseTime      = 500;
    m_config.refreshBleachingVoltage    = 1.1;
    m_config.refreshBleachPulseTime     = 100;
    m_config.refreshBleachLimitLVoltage = 0.45;
}

template <>
inline ECD<3>::ECD(const std::array<int, 3>& pins)
    : m_pins(pins), m_states({}), m_nextStates({}), m_config(getConfigDefaults())
{
    m_config.coloringTime            = 1200;
    m_config.bleachingTime           = 1000;
    m_config.refreshColoringVoltage  = 1.4;
    m_config.refreshColorPulseTime   = 150;
    m_config.refreshBleachingVoltage = 1.1;
    m_config.refreshBleachPulseTime  = 300;
}

template <>
inline ECD<7>::ECD(const std::array<int, 7>& pins)
    : m_pins(pins), m_states({}), m_nextStates({}), m_config(getConfigDefaults())
{
    m_config.refreshBleachLimitLVoltage = 0.4;
    m_config.bleachingTime              = 1000;
}

template <>
inline ECD<8>::ECD(const std::array<int, 8>& pins)
    : m_pins(pins), m_states({}), m_nextStates({}), m_config(getConfigDefaults())
{
}

template <>
inline ECD<15>::ECD(const std::array<int, 15>& pins)
    : m_pins(pins), m_states({}), m_nextStates({}), m_config(getConfigDefaults())
{
    m_config.refreshColoringVoltage     = 1.4;
    m_config.refreshColorLimitHVoltage  = 1.0;
    m_config.refreshBleachPulseTime     = 100;
    m_config.refreshBleachLimitLVoltage = 0.5;
}

class EvalkitDisplays
{
   public:
    // Enum for display indices
    enum ECDEvalkitDisplay_t
    {
        EVALKIT_DISP_SINGLE_SEGMENT_DISPLAY = 0,  // DISP442V2PV1, DISP443V2PV1, DISP437V2PV1, DISP440V2PV1
        EVALKIT_DISP_THREE_SEGMENT_BAR_DISPLAY,   // DISP438V2PV1
        EVALKIT_DISP_SEVEN_SEGMENT_BAR_DISPLAY,   // DISP431V2PV1
        EVALKIT_DISP_DOT_NUMBER_DISPLAY,          // DISP434V1PV1
        EVALKIT_DISP_DECIMAL_NUMBER_DISPLAY,      // DISP433V1PV1
        EVALKIT_DISP_SIGNED_NUMBER_DISPLAY,       // DISP444V1PV2
        EVALKIT_DISP_CNT
    };

    // Singleton accessor
    static EvalkitDisplays& getInstance()
    {
        static EvalkitDisplays instance;
        return instance;
    }

    // Operator[] to access displays by index
    ECDBase* operator[](ECDEvalkitDisplay_t idx) const { return m_displays[idx]; }

    void init()
    {
        ynv::ecd::ECDBase::init();  // Initialize the ECD driving
        delay(100);                 // Wait for the ECD to stabilize
    }

   private:
    // Private constructor for singleton
    EvalkitDisplays()
        : singleSegmentDisplay(singleSegmentDisplayPins),
          threeSegmentBarDisplay(threeSegmentBarDisplayPins),
          sevenSegmentBarDisplay(sevenSegmentBarDisplayPins),
          dotNumberDisplay(dotNumberDisplayPins),
          decimalNumberDisplay(decimalNumberDisplayPins),
          signedNumberDisplay(signedNumberDisplayPins),
          m_displays {&singleSegmentDisplay, &threeSegmentBarDisplay, &sevenSegmentBarDisplay,
                      &dotNumberDisplay,     &decimalNumberDisplay,   &signedNumberDisplay}
    {
    }

    // Delete copy/move to enforce singleton
    EvalkitDisplays(const EvalkitDisplays&)            = delete;
    EvalkitDisplays& operator=(const EvalkitDisplays&) = delete;

    // Pin arrays
    const std::array<int, 1>  singleSegmentDisplayPins {PIN_SEG_1};
    const std::array<int, 3>  threeSegmentBarDisplayPins {PIN_SEG_2, PIN_SEG_1, PIN_SEG_3};
    const std::array<int, 7>  sevenSegmentBarDisplayPins {PIN_SEG_4, PIN_SEG_3, PIN_SEG_5, PIN_SEG_2,
                                                         PIN_SEG_6, PIN_SEG_1, PIN_SEG_7};
    const std::array<int, 8>  dotNumberDisplayPins {PIN_SEG_8, PIN_SEG_7, PIN_SEG_5, PIN_SEG_6,
                                                   PIN_SEG_4, PIN_SEG_3, PIN_SEG_1, PIN_SEG_2};
    const std::array<int, 15> decimalNumberDisplayPins {PIN_SEG_8,  PIN_SEG_1,  PIN_SEG_7, PIN_SEG_6,  PIN_SEG_5,
                                                        PIN_SEG_4,  PIN_SEG_2,  PIN_SEG_3, PIN_SEG_14, PIN_SEG_13,
                                                        PIN_SEG_11, PIN_SEG_10, PIN_SEG_9, PIN_SEG_15, PIN_SEG_12};
    const std::array<int, 15> signedNumberDisplayPins {PIN_SEG_4,  PIN_SEG_2,  PIN_SEG_1, PIN_SEG_8,  PIN_SEG_7,
                                                       PIN_SEG_6,  PIN_SEG_3,  PIN_SEG_5, PIN_SEG_14, PIN_SEG_13,
                                                       PIN_SEG_11, PIN_SEG_10, PIN_SEG_9, PIN_SEG_15, PIN_SEG_12};

    // Display objects
    DispSingleSegment singleSegmentDisplay;
    Disp3SegBar       threeSegmentBarDisplay;
    Disp7SegBar       sevenSegmentBarDisplay;
    DispDotNumber     dotNumberDisplay;
    DispDecimalNumber decimalNumberDisplay;
    DispSignedNumber  signedNumberDisplay;

    // Array of pointers to base class for polymorphic access
    // IMPORTANT: use ECDEvalkitDisplay_t as index
    const std::array<ECDBase*, EVALKIT_DISP_CNT> m_displays;
};

}  // namespace ecd
}  // namespace ynv