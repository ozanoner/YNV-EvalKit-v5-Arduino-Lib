#pragma once

#include <Arduino.h>

#include <array>
#include <cassert>
#include <cinttypes>
#include <vector>

#include "app_config.h"
#include "ecd_drive_base.h"

#if ACTIVE_DRIVING
#include "ecd_drive_active.h"
#else
#include "ecd_drive_passive.h"
#endif

namespace ynv
{
namespace ecd
{

class ECDBase
{
   public:
    ~ECDBase() = default;

    virtual void init()                               = 0;  // Initialize the ECD
    virtual void reset()                              = 0;  // Reset the ECD to bleach state
    virtual void set()                                = 0;  // Set all segments to color state
    virtual void set(const std::vector<bool>& states) = 0;  // Set segments to specified states
    virtual void update()                             = 0;  // Apply m_nextStates to hardware
    virtual void toggle()                             = 0;  // Toggle the state of all segments
    virtual void printConfig() const                  = 0;  // Print the configuration of the ECD
};

template <int SEGMENT_COUNT>
class ECD : public ECDBase
{
   public:
    ECD(const std::array<int, SEGMENT_COUNT>* pins, const ynv::app::AppConfig_t* appConfig)
        : m_pins(pins), m_states({}), m_nextStates({}), m_driver(&m_config, pins), m_appConfig(appConfig)
    {
        assert(m_appConfig != nullptr);
    }

    ~ECD() = default;

    void init() override
    {
        m_config.maxAnalogValue = (1 << m_appConfig->analogResolution) - 1;  // Set max analog value based on resolution
        initConfig();  // Initialize the ECD with default configuration
        validateConfig();
    }

    void reset() override
    {
        m_nextStates.fill(false);  // All segments to bleach state
    }

    void set() override
    {
        m_nextStates.fill(true);  // All segments to color state
    }

    void toggle() override
    {
        for (int i = 0; i < SEGMENT_COUNT; ++i)
        {
            m_nextStates[i] = !m_states[i];  // Toggle each segment state
        }
    }

    void set(const std::vector<bool>& states) override
    {
        assert(states.size() == SEGMENT_COUNT);
        std::copy(states.begin(), states.end(), m_nextStates.begin());
    }

    // Animation will call this method to apply the next states to the hardware in the Arduino loop.
    // NOTE: The total execution time may exceed one cycle of the animation.
    void update() override
    {
        m_driver.drive(m_states, m_nextStates);  // Drive the segments based on current and next states
    }

    void printConfig() const override
    {
        m_config.print();  // Print the configuration of the ECD
    }

   protected:
    const std::array<int, SEGMENT_COUNT>* m_pins;        // Array to hold segment pin numbers
    std::array<bool, SEGMENT_COUNT>       m_states;      // Array to hold segment states (bleach=false or color=true)
    std::array<bool, SEGMENT_COUNT>       m_nextStates;  // Array to hold next states for segments
    ECDConfig_t                           m_config;      // Configuration for the ECD
#if ACTIVE_DRIVING
    ECDDriveActive<SEGMENT_COUNT> m_driver;  // Active driving algorithm
#else
    ECDDrivePassive<SEGMENT_COUNT> m_driver;  // Passive driving algorithm
#endif
    const ynv::app::AppConfig_t* m_appConfig;

    virtual void initConfig() = 0;  // Initialize the ECD with default configuration

    void validateConfig()
    {
        assert(m_config.maxAnalogValue > 0);
        assert(m_config.coloringVoltage > 0);
        assert(m_config.bleachingVoltage > 0);
        assert(m_config.refreshColoringVoltage > 0);
        assert(m_config.refreshBleachingVoltage > 0);
        assert(m_config.refreshColorLimitHVoltage > 0);
        assert(m_config.refreshColorLimitLVoltage > 0);
        assert(m_config.refreshBleachLimitHVoltage > 0);
        assert(m_config.refreshBleachLimitLVoltage > 0);
        assert(m_config.coloringTime > 0);
        assert(m_config.bleachingTime > 0);
        assert(m_config.refreshColorPulseTime > 0);
        assert(m_config.refreshBleachPulseTime > 0);

        assert(m_config.coloringVoltage < m_config.maxAnalogValue);
        assert(m_config.bleachingVoltage < m_config.maxAnalogValue);
        assert(m_config.refreshColoringVoltage < m_config.maxAnalogValue);
        assert(m_config.refreshBleachingVoltage < m_config.maxAnalogValue);
        assert(m_config.refreshColorLimitHVoltage < m_config.maxAnalogValue &&
               m_config.refreshColorLimitHVoltage > (m_config.maxAnalogValue / 2));
        assert(m_config.refreshColorLimitLVoltage < m_config.maxAnalogValue &&
               m_config.refreshColorLimitLVoltage > (m_config.maxAnalogValue / 2));
        assert(m_config.refreshBleachLimitHVoltage < (m_config.maxAnalogValue / 2));
        assert(m_config.refreshBleachLimitLVoltage < (m_config.maxAnalogValue / 2));
    }

    static constexpr std::array<uint8_t, 10> numberMask()
    {
        return {
            0b10111111,  // 0
            0b10000110,  // 1
            0b11011011,  // 2
            0b11001111,  // 3
            0b11100110,  // 4
            0b11101101,  // 5
            0b11111101,  // 6
            0b10000111,  // 7
            0b11111111,  // 8
            0b11101111   // 9
        };
    }
};

}  // namespace ecd
}  // namespace ynv