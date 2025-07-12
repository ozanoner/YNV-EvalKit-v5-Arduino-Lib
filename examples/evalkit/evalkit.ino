
#include <Arduino.h>

#include "evalkitv5_led_array.h"

void setup()
{
    pinMode(MCU_PWR_ON, OUTPUT);  // Keep the Board Power ON
    digitalWrite(MCU_PWR_ON, HIGH);
    delay(1000);  

    Serial.begin(9600);
    Serial.println("Hello, EvalKit!");
    delay(1000);  // Wait for 1 second to ensure the LEDs are initialized
    ynv::board::hal::LEDArray::getInstance().init();
    delay(1000);  // Wait for 1 second to ensure the LEDs are initialized
}

void loop()
{
    static bool run = true;

    while (run)
    {
        ynv::board::hal::LEDArray::getInstance().patternTest();

        run = false;  // Stop after one complete cycle
    }

    delay(1000);  // Wait for 1 second
}