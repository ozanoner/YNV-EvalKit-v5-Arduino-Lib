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
    ~ECDBase() { }

    static void init(const ynv::app::AppConfig_t* appConfig);  // Initialize the ECD hardware

    virtual void reset()                              = 0;  // Reset the ECD to bleach state
    virtual void set()                                = 0;  // Set all segments to color state
    virtual void set(const std::vector<bool>& states) = 0;  // Set segments to specified states
    virtual void update()                             = 0;  // Apply m_nextStates to hardware
    virtual void toggle()                             = 0;  // Toggle the state of all segments
    virtual void printConfig() const                  = 0;  // Print the configuration of the ECD

   protected:
    static constexpr int ADC_DAC_RESOLUTION = 10;                             // 10-bit resolution for ADC and DAC
    static constexpr int ADC_DAC_MAX_LSB    = (1 << ADC_DAC_RESOLUTION) - 1;  // Maximum value for 10-bit resolution

    // Scale factor for voltage mapping, 0.67 for 2V, 1.0 for 3V, 1.1 for 3.3V, etc.
    // Update m_appConfig->supplyVoltage if using a different voltage.
    static constexpr float VOLTAGE_SCALE = 1.0f;

    inline static const ynv::app::AppConfig_t* m_appConfig = nullptr;
};

template <int SEGMENT_COUNT = 1>
class ECD : public ECDBase
{
   public:
    ECD(const std::array<int, SEGMENT_COUNT>& pins)
        : m_pins(pins), m_states({}), m_nextStates({}), m_config(getConfigDefaults()), m_driver(m_config, pins)
    {
    }

    ~ECD() = default;

    using ECDBase::m_appConfig;

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

    // Implements the active driving of the ECD segments as described in the datasheet.
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
    const std::array<int, SEGMENT_COUNT> m_pins;        // Array to hold segment pin numbers
    std::array<bool, SEGMENT_COUNT>      m_states;      // Array to hold segment states (bleach=false or color=true)
    std::array<bool, SEGMENT_COUNT>      m_nextStates;  // Array to hold next states for segments
    ECDConfig_t                          m_config;      // Configuration for the ECD
#if ACTIVE_DRIVING
    ECDDriveActive<SEGMENT_COUNT> m_driver;  // Active driving algorithm
#else
    ECDDrivePassive<SEGMENT_COUNT> m_driver;  // Passive driving algorithm
#endif

    static constexpr ECDConfig_t getConfigDefaults()
    {
        return {
            // coloringVoltage
            (int)((m_appConfig->supplyVoltage - 1.5f * VOLTAGE_SCALE) / m_appConfig->supplyVoltage * ADC_DAC_MAX_LSB),
            500,  // coloringTime

            // bleachingVoltage
            (int)(1.2f * VOLTAGE_SCALE / m_appConfig->supplyVoltage * ADC_DAC_MAX_LSB),
            500,  // bleachingTime

            // refreshColoringVoltage
            (int)((m_appConfig->supplyVoltage - 1.3f * VOLTAGE_SCALE) / m_appConfig->supplyVoltage * ADC_DAC_MAX_LSB),
            100,  // refreshColorPulseTime

            // refreshColorLimitHVoltage
            (int)((m_appConfig->supplyVoltage - 0.2f * VOLTAGE_SCALE) / m_appConfig->supplyVoltage * ADC_DAC_MAX_LSB),
            // refreshColorLimitLVoltage
            (int)((m_appConfig->supplyVoltage / 2 + 0.9f * VOLTAGE_SCALE) / m_appConfig->supplyVoltage *
                  ADC_DAC_MAX_LSB),

            // refreshBleachingVoltage
            (int)(0.9f * VOLTAGE_SCALE / m_appConfig->supplyVoltage * ADC_DAC_MAX_LSB),
            50,  // refreshBleachPulseTime

            // refreshBleachLimitHVoltage
            (int)((m_appConfig->supplyVoltage / 2 - 0.2f * VOLTAGE_SCALE) / m_appConfig->supplyVoltage *
                  ADC_DAC_MAX_LSB),
            // refreshBleachLimitLVoltage
            (int)((0.3f * VOLTAGE_SCALE) / m_appConfig->supplyVoltage * ADC_DAC_MAX_LSB),
        };
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