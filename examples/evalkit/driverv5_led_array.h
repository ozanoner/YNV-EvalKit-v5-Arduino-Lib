
#pragma once

#include <Arduino.h>

#include <array>

namespace ynv
{
namespace driverv5
{

class LEDArray
{
   public:
    static LEDArray& getInstance()
    {
        static LEDArray instance;
        return instance;
    }

    void init();

    void clear();

    // 0 -> all leds off
    void show(unsigned int number);

    void patternTest();

   private:
    LEDArray()                           = default;
    ~LEDArray()                          = default;
    LEDArray(const LEDArray&)            = delete;
    LEDArray& operator=(const LEDArray&) = delete;

    inline static constexpr std::array<unsigned int, 7> LED_PINS = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};
};

}  // namespace driverv5
}  // namespace ynv