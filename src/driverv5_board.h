/**
 * @file driverv5_board.h
 * @brief  Driver V5 board HAL.
 * This header defines the Driver V5 board interface, including buttons, LED array, and RGB LED.
 * It provides a singleton interface for easy access to the board components.
 * @version 0.1
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <Arduino.h>

#include "app_config.h"
#include "driverv5_buttons.h"
#include "driverv5_led_array.h"
#include "driverv5_rgb_led.h"

namespace ynv
{
namespace driverv5
{

/**
 * @brief  Driver V5 board HAL.
 * This class provides access to the board's components, including buttons, LED array, and RGB LED.
 */
class Board
{
   public:
    static Board& getInstance()
    {
        static Board instance;
        return instance;
    }

    void init(const ynv::app::AppConfig_t* appConfig);

    LEDArray& getLEDArray() { return m_ledArray; }
    RGBLED&   getRGBLED() { return m_rgbLED; }
    Buttons&  getButtons() { return m_buttons; }
    void      handleEvents() { m_buttons.handle(); }

    void enableButtonTest();

   private:
    Board()                        = default;
    ~Board()                       = default;
    Board(const Board&)            = delete;
    Board& operator=(const Board&) = delete;

    LEDArray& m_ledArray = LEDArray::getInstance();
    RGBLED&   m_rgbLED   = RGBLED::getInstance();
    Buttons&  m_buttons  = Buttons::getInstance();

    const ynv::app::AppConfig_t* m_appConfig = nullptr;
};

}  // namespace driverv5
}  // namespace ynv