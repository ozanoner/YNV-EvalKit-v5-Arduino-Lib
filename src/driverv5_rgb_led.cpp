
#include "driverv5_rgb_led.h"

#include <Arduino.h>

namespace ynv
{
namespace driverv5
{
void RGBLED::init()
{
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    blue();
}

void RGBLED::red()
{
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
}

void RGBLED::blue()
{
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
}

void RGBLED::green()
{
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
}

void RGBLED::off()
{
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);  // Turn off all LEDs
}

}  // namespace driverv5
}  // namespace ynv