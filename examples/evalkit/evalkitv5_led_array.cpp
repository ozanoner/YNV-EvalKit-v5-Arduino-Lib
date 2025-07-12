#include "evalkitv5_led_array.h"

#include <Arduino.h>

#include <cinttypes>

namespace ynv
{
namespace board
{
namespace hal
{

void LEDArray::init()
{
    for (auto pin : LED_PINS)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);  // Set all LEDs to off initially
    }

    // a simple test pattern to show the LEDs are working
    for (auto pin : LED_PINS)
    {
        digitalWrite(pin, LOW);
        delay(50);
    }
    for (auto it = LED_PINS.rbegin(); it != LED_PINS.rend(); ++it)
    {
        digitalWrite(*it, HIGH);
        delay(50);
    }
}

void LEDArray::clear()
{
    for (unsigned int pin : LED_PINS)
    {
        digitalWrite(pin, HIGH);
    }
}

void LEDArray::show(unsigned int number)
{
    static const std::array<uint8_t, 29> LED_PATTERN = {
        0b11111111,  // 0
        0b11111110,  // 1
        0b11111101,  // 2
        0b11111011,  // 3
        0b11110111,  // 4
        0b11101111,  // 5
        0b11011111,  // 6
        0b10111111,  // 7
        0b11111100,  // 8
        0b11111010,  // 9
        0b11110110,  // 10
        0b11101110,  // 11
        0b11011110,  // 12
        0b10111110,  // 13
        0b11111000,  // 14
        0b11110100,  // 15
        0b11101100,  // 16
        0b11011100,  // 17
        0b10111100,  // 18
        0b11110000,  // 19
        0b11101000,  // 20
        0b11011000,  // 21
        0b10111000,  // 22
        0b11100000,  // 23
        0b11010000,  // 24
        0b10110000,  // 25
        0b11000000,  // 26
        0b10100000,  // 27
        0b10000000,  // 28
    };

    if (number > 28)
    {
        number = 0;
    }

    uint8_t pattern = LED_PATTERN[number];
    for (int i = 0; i < LED_PINS.size(); ++i)
    {
        digitalWrite(LED_PINS[i], bitRead(pattern, i) ? HIGH : LOW);
    }
}

void LEDArray::patternTest()
{
    for (int i = 1; i <= 28; ++i)
    {
        LEDArray::show(i);
        Serial.print("Showing pattern for: ");
        Serial.println(i);
        delay(500);  // Wait for 0.5 seconds to see the pattern
    }
    LEDArray::clear();
    Serial.println("LEDs cleared.");
}

}  // namespace hal
}  // namespace board
}  // namespace ynv
