#pragma once

#include <Arduino.h>

#include <array>
#include <cassert>
#include <cinttypes>
#include <vector>

namespace ynv
{
namespace ecd
{

class ECDBase
{
   public:
    ~ECDBase() { }

    static void init();  // Initialize the ECD hardware

    virtual void reset()                              = 0;  // Reset the ECD to bleach state
    virtual void set()                                = 0;  // Set all segments to color state
    virtual void set(const std::vector<bool>& states) = 0;  // Set segments to specified states
    virtual void update()                             = 0;  // Apply m_nextStates to hardware
    virtual void toggle()                             = 0;  // Toggle the state of all segments

   protected:
    static constexpr int   ADC_DAC_RESOLUTION = 10;                             // 10-bit resolution for ADC and DAC
    static constexpr int   ADC_DAC_MAX_LSB    = (1 << ADC_DAC_RESOLUTION) - 1;  // Maximum value for 10-bit resolution
    static constexpr float SUPPLY_VOLTAGE     = 3.0f;                           // Supply voltage for the ECD
};

template <int SEGMENT_COUNT = 1>
class ECD : public ECDBase
{
   public:
    typedef struct
    {
        // Color & Bleach Configs
        float coloringVoltage;  // V - Absolute value for Color Pulse Voltage
        int   coloringTime;     // ms - Color time

        float bleachingVoltage;  // V - Absolute value for Bleach Pulse Voltage
        int   bleachingTime;     // ms - Bleach time

        // Refresh Configs
        float refreshColoringVoltage;   // V - Absolute value for Refresh Coloring Pulses Voltage
        float refreshBleachingVoltage;  // V - Absolute value for Refresh Bleaching Pulses Voltage

        float refreshColorLimitHVoltage;
        float refreshColorLimitLVoltage;
        float refreshBleachLimitHVoltage;
        float refreshBleachLimitLVoltage;

        int refreshColorPulseTime;  // ms - Delay between each Refresh Pulse
        int refreshBleachPulseTime;
    } ECDConfig_t;

    ECD(const std::array<int, SEGMENT_COUNT>& pins)
        : m_pins(pins), m_states({}), m_nextStates({}), m_config(getConfigDefaults())
    {
    }
    ~ECD() { }

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

    void update() override
    {
        // Apply m_nextStates to hardware (implementation depends on hardware specifics)
        // and set m_states to m_nextStates.
        // Run in the loop
    }

   protected:
    const std::array<int, SEGMENT_COUNT> m_pins;        // Array to hold segment pin numbers
    std::array<bool, SEGMENT_COUNT>      m_states;      // Array to hold segment states (bleach=false or color=true)
    std::array<bool, SEGMENT_COUNT>      m_nextStates;  // Array to hold next states for segments

    void enableCounterElectrode(float val);  // Enable the counter electrode with a specified value
    void disableCounterElectrode();          // Disable the counter electrode

    ECDConfig_t                  m_config;  // Configuration for the ECD
    static constexpr ECDConfig_t getConfigDefaults()
    {
        return {
            1.5f,  // coloringVoltage
            500,   // coloringTime
            1.2f,  // bleachingVoltage
            500,   // bleachingTime
            1.3f,  // refreshColoringVoltage
            0.9f,  // refreshBleachingVoltage
            1.1f,  // refreshColorLimitHVoltage
            0.9f,  // refreshColorLimitLVoltage
            0.2f,  // refreshBleachLimitHVoltage
            0.6f,  // refreshBleachLimitLVoltage
            100,   // refreshColorPulseTime
            50     // refreshBleachPulseTime
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