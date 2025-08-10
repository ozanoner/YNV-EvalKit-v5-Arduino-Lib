/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief  Main application entry point for the ESP32 MCU communication example.
 * @version 0.1
 * @date 2025-08-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mcu_comm.hpp"

namespace
{
app::comm::McuComm& m_comm = app::comm::McuComm::getInstance();
}

extern "C" void app_main(void)
{
    esp_err_t err = m_comm.init();
    if (err != ESP_OK)
    {
        return;
    }

    while (true)
    {
        // select the next animation
        (void)m_comm.send(app::comm::McuComm::CMD_BTN_DOWN_PRESSED);
        // 100ms delay before the next step
        vTaskDelay(pdMS_TO_TICKS(100));
        // start the animation
        (void)m_comm.send(app::comm::McuComm::CMD_BTN_START_PRESSED);
        // run the current animation for 30 seconds
        vTaskDelay(pdMS_TO_TICKS(30000));
        // abort the animation
        (void)m_comm.send(app::comm::McuComm::CMD_BTN_START_LONG_PRESSED);
        // 1 sec delay before the next step
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
