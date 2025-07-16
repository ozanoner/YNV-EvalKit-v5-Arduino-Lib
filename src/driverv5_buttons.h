
#pragma once

#include <Arduino.h>

#include <array>

namespace ynv
{
namespace driverv5
{

class Buttons
{
   public:
    static constexpr int DRIVER_BUTTON_DEBOUNCE_MS   = 50;
    static constexpr int DRIVER_BUTTON_LONG_PRESS_MS = 1000;

    enum ButtonPress_t
    {
        BTN_START_PRESSED,
        BTN_START_LONG_PRESSED,
        BTN_UP_PRESSED,
        BTN_DOWN_PRESSED,
        BTN_NONE
    };

    using ButtonCb_f = void (*)(ButtonPress_t);

    static Buttons& getInstance()
    {
        static Buttons instance;
        return instance;
    }

    void init();
    void handle();
    void registerCallback(ButtonCb_f callback);

   private:
    Buttons() : m_buttonCallback(nullptr), m_buttonEvents({}) { }
    ~Buttons()                         = default;
    Buttons(const Buttons&)            = delete;
    Buttons& operator=(const Buttons&) = delete;

    static void buttonStartPressedISR();
    static void buttonUpPressedISR();
    static void buttonDownPressedISR();

    ButtonCb_f m_buttonCallback = nullptr;  // Callback function for button presses

    std::array<volatile bool, BTN_NONE> m_buttonEvents;  // Array to track button events
};

}  // namespace driverv5
}  // namespace ynv