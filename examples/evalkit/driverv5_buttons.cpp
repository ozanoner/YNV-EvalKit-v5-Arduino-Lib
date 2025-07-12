#include "driverv5_buttons.h"

#include <Arduino.h>

namespace ynv
{
namespace driverv5
{

void Buttons::init()
{
    pinMode(BTN_START, INPUT);
    pinMode(BTN_UP, INPUT);
    pinMode(BTN_DOWN, INPUT);

    attachInterrupt(digitalPinToInterrupt(BTN_START), buttonStartPressedISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BTN_UP), buttonUpPressedISR, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_DOWN), buttonDownPressedISR, RISING);
    interrupts();
}

void Buttons::handle()
{
    if (m_buttonCallback == nullptr)
    {
        return;  // No callback registered
    }

    for (size_t i = 0; i < BTN_NONE; ++i)
    {
        if (m_buttonEvents[i])
        {
            m_buttonCallback((ButtonPress_t)i);  // Call the registered callback for the button press
            m_buttonEvents[i] = false;           // Reset the event after handling
        }
    }
}

void Buttons::registerCallback(ButtonCb_f callback)
{
    m_buttonCallback = callback;  // Register the callback function for button presses
}

void Buttons::buttonStartPressedISR()
{
    static long last = 0;
    long        now  = millis();

    // Button pressed
    if (digitalRead(BTN_START) == LOW)
    {
        last = now;
        return;
    }

    // Button released
    if ((now - last) < DRIVER_BUTTON_DEBOUNCE_MS)
    {
        // Ignore if released too quickly (debounce)
        return;
    }

    if ((now - last) < DRIVER_BUTTON_LONG_PRESS_MS)
    {
        getInstance().m_buttonEvents[BTN_START_PRESSED] = true;  // Short press
    }
    else
    {
        getInstance().m_buttonEvents[BTN_START_LONG_PRESSED] = true;  // Long press
    }
}

void Buttons::buttonUpPressedISR()
{
    static long last = 0;
    long        now  = millis();

    // Button pressed (RISING edge)
    if ((now - last) < DRIVER_BUTTON_DEBOUNCE_MS)
    {
        // Ignore if pressed too quickly (debounce)
        return;
    }
    last                                         = now;
    getInstance().m_buttonEvents[BTN_UP_PRESSED] = true;
}

void Buttons::buttonDownPressedISR()
{
    static long last = 0;
    long        now  = millis();

    // Button pressed (RISING edge)
    if ((now - last) < DRIVER_BUTTON_DEBOUNCE_MS)
    {
        // Ignore if pressed too quickly (debounce)
        return;
    }
    last                                           = now;
    getInstance().m_buttonEvents[BTN_DOWN_PRESSED] = true;
}

}  // namespace driverv5
}  // namespace ynv