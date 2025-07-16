#include "ecd.h"

#include <Arduino.h>

#include <cassert>

namespace ynv
{
namespace ecd
{

void ECDBase::init(const ynv::app::AppConfig_t* appConfig)
{
    assert(appConfig != nullptr);
    m_appConfig = appConfig;

    analogReadResolution(ADC_DAC_RESOLUTION);
    analogWriteResolution(ADC_DAC_RESOLUTION);
}

}  // namespace ecd
}  // namespace ynv