#include "ecd.h"

#include <Arduino.h>

#include <cassert>

namespace ynv
{
namespace ecd
{

void ECDBase::init()
{
    analogReadResolution(ADC_DAC_RESOLUTION);
    analogWriteResolution(ADC_DAC_RESOLUTION);
}

template <int SEGMENT_COUNT>
void ECD<SEGMENT_COUNT>::enableCounterElectrode(float val)
{
    pinMode(PIN_CE, OUTPUT);
    analogWrite(PIN_CE, int(ADC_DAC_MAX_LSB * (val / SUPPLY_VOLTAGE)));
    delay(50);
}

template <int SEGMENT_COUNT>
void ECD<SEGMENT_COUNT>::disableCounterElectrode()
{
    pinMode(PIN_CE, INPUT);  // Set the counter electrode pin to input to disable it
}

}  // namespace ecd
}  // namespace ynv