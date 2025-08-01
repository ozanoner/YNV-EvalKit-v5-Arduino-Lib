#pragma once

#include <Arduino.h>

#include <array>
#include <cassert>
#include <memory>

#include "app_config.h"
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

    void init(const ynv::app::AppConfig_t* appConfig)
    {
        assert(appConfig != nullptr);
        m_appConfig = appConfig;  // Store the application configuration
        assert(appConfig->displayIndex >= 0 && appConfig->displayIndex < EVALKIT_DISP_CNT);

        switch (appConfig->displayIndex)
        {
            case EVALKIT_DISP_SINGLE_SEGMENT_DISPLAY:
                m_displayPtr = std::make_shared<DispSingleSegment>(&singleSegmentDisplayPins, m_appConfig);
                break;
            case EVALKIT_DISP_THREE_SEGMENT_BAR_DISPLAY:
                m_displayPtr = std::make_shared<Disp3SegBar>(&threeSegmentBarDisplayPins, m_appConfig);
                break;
            case EVALKIT_DISP_SEVEN_SEGMENT_BAR_DISPLAY:
                m_displayPtr = std::make_shared<Disp7SegBar>(&sevenSegmentBarDisplayPins, m_appConfig);
                break;
            case EVALKIT_DISP_DOT_NUMBER_DISPLAY:
                m_displayPtr = std::make_shared<DispDotNumber>(&dotNumberDisplayPins, m_appConfig);
                break;
            case EVALKIT_DISP_DECIMAL_NUMBER_DISPLAY:
                m_displayPtr = std::make_shared<DispDecimalNumber>(&decimalNumberDisplayPins, m_appConfig);
                break;
            case EVALKIT_DISP_SIGNED_NUMBER_DISPLAY:
                m_displayPtr = std::make_shared<DispSignedNumber>(&signedNumberDisplayPins, m_appConfig);
                break;
            default:
                break;
        }

        if (m_displayPtr != nullptr)
        {
            m_displayPtr->init();
        }
    }

    std::shared_ptr<ECDBase> getDisplay()
    {
        assert(m_displayPtr != nullptr);
        return m_displayPtr;
    }

   private:
    // Private constructor for singleton
    EvalkitDisplays() : m_displayPtr(nullptr), m_appConfig(nullptr) { }

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

    std::shared_ptr<ECDBase>     m_displayPtr;  // Pointer to the current display
    const ynv::app::AppConfig_t* m_appConfig;
};

}  // namespace ecd
}  // namespace ynv