
#pragma once

#include <Arduino.h>

#include <array>

namespace ynv
{
namespace ecd
{

struct ECDConfig_t
{
    int maxAnalogValue;  // Maximum analog value for the ECD

    // Color & Bleach Configs
    int coloringVoltage;  // V - Color Pulse Voltage mapped to ADC_DAC_MAX_LSB
    int coloringTime;     // ms - Color time

    int bleachingVoltage;  // V - Bleach Pulse Voltage mapped to ADC_DAC_MAX_LSB
    int bleachingTime;     // ms - Bleach time

    // Refresh Configs
    int refreshColoringVoltage;  // V - Refresh Coloring Pulses Voltage mapped to ADC_DAC_MAX_LSB
    int refreshColorPulseTime;   // ms - Delay between each Refresh Pulse

    int refreshColorLimitHVoltage;
    int refreshColorLimitLVoltage;

    int refreshBleachingVoltage;  // V - Refresh Bleaching Pulses Voltage mapped to ADC_DAC_MAX_LSB
    int refreshBleachPulseTime;

    int refreshBleachLimitHVoltage;
    int refreshBleachLimitLVoltage;

    void print() const
    {
        Serial.println(F("-------------------------------------------------------------"));
        Serial.println(F("Parameter                  | Value"));
        Serial.println(F("-------------------------------------------------------------"));
        Serial.print(F("maxAnalogValue             | "));
        Serial.println(maxAnalogValue);
        Serial.print(F("coloringVoltage            | "));
        Serial.println(coloringVoltage);
        Serial.print(F("coloringTime               | "));
        Serial.println(coloringTime);
        Serial.print(F("bleachingVoltage           | "));
        Serial.println(bleachingVoltage);
        Serial.print(F("bleachingTime              | "));
        Serial.println(bleachingTime);
        Serial.print(F("refreshColoringVoltage     | "));
        Serial.println(refreshColoringVoltage);
        Serial.print(F("refreshColorPulseTime      | "));
        Serial.println(refreshColorPulseTime);
        Serial.print(F("refreshColorLimitHVoltage  | "));
        Serial.println(refreshColorLimitHVoltage);
        Serial.print(F("refreshColorLimitLVoltage  | "));
        Serial.println(refreshColorLimitLVoltage);
        Serial.print(F("refreshBleachingVoltage    | "));
        Serial.println(refreshBleachingVoltage);
        Serial.print(F("refreshBleachPulseTime     | "));
        Serial.println(refreshBleachPulseTime);
        Serial.print(F("refreshBleachLimitHVoltage | "));
        Serial.println(refreshBleachLimitHVoltage);
        Serial.print(F("refreshBleachLimitLVoltage | "));
        Serial.println(refreshBleachLimitLVoltage);
        Serial.println(F("-------------------------------------------------------------"));
    }
};

template <int SEGMENT_COUNT>
class ECDDriveBase
{
   public:
    ECDDriveBase(const ECDConfig_t* config, const std::array<int, SEGMENT_COUNT>* pins) : m_config(config), m_pins(pins)
    {
    }

    virtual ~ECDDriveBase() = default;

    virtual void drive(std::array<bool, SEGMENT_COUNT>&       currentStates,  // current states of the segments
                       const std::array<bool, SEGMENT_COUNT>& nextStates      // next states of the segments
                       ) = 0;

   protected:
    const ECDConfig_t*                    m_config;  // Configuration for the ECD
    const std::array<int, SEGMENT_COUNT>* m_pins;    // Pin numbers for the segments

    void enableCounterElectrode(int val)
    {
        pinMode(PIN_CE, OUTPUT);
        analogWrite(PIN_CE, val);
        delay(50);
    }

    void disableCounterElectrode()
    {
        pinMode(PIN_CE, INPUT);  // Set the counter electrode pin to input to disable it
    }
};
}  // namespace ecd
}  // namespace ynv