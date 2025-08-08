/**
 * @file driverv5_board.cpp
 * @brief  Driver V5 board HAL implementation.
 * @version 0.1
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "driverv5_board.h"

#include <Arduino.h>

#include <cassert>

#include "app_config.h"

namespace ynv
{
namespace driverv5
{

void Board::init(const ynv::app::AppConfig_t* appConfig)
{
    assert(appConfig != nullptr);
    m_appConfig = appConfig;

    assert(m_appConfig->analogResolution > 8 && m_appConfig->analogResolution <= 16);
    analogReadResolution(m_appConfig->analogResolution);
    analogWriteResolution(m_appConfig->analogResolution);

    pinMode(MCU_PWR_ON, OUTPUT);  // Keep the Board Power ON
    digitalWrite(MCU_PWR_ON, HIGH);
    delay(1000);

    Serial.begin(9600);
    delay(1000);

    m_buttons.init();
    m_rgbLED.init();
    m_ledArray.init();
    delay(1000);
}

void Board::enableButtonTest()
{
    m_buttons.registerCallback(
        [](Buttons::ButtonPress_t buttonEvent)
        {
            switch (buttonEvent)
            {
                case Buttons::BTN_START_PRESSED:
                    Board::getInstance().getRGBLED().red();
                    Serial.println("BTN_START_PRESSED");
                    break;
                case Buttons::BTN_START_LONG_PRESSED:
                    Board::getInstance().getRGBLED().off();
                    Serial.println("BTN_START_LONG_PRESSED");
                    break;
                case Buttons::BTN_UP_PRESSED:
                    Board::getInstance().getRGBLED().green();
                    Serial.println("BTN_UP_PRESSED");
                    break;
                case Buttons::BTN_DOWN_PRESSED:
                    Board::getInstance().getRGBLED().blue();
                    Serial.println("BTN_DOWN_PRESSED");
                    break;
                default:
                    break;
            }
        });
}

}  // namespace driverv5
}  // namespace ynv