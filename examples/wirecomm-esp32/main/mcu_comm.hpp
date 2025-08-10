/**
 * @file mcu_comm.hpp
 * @brief  MCU communication handler for I2C commands.
 * This class handles communication with the MCU over I2C, allowing sending commands
 * to the Ynvisible Eval Kit.
 * @version 0.1
 * @date 2025-08-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "esp_err.h"
#include "i2c_conn.hpp"

namespace app
{
namespace comm
{

/**
 * @brief The class that implements the inter-MCU protocol.
 */
class McuComm
{
   public:
    // Singleton access
    static McuComm& getInstance()
    {
        static McuComm instance;
        return instance;
    }

    // Duplication of button events from the driver
    enum Command_t
    {
        CMD_BTN_START_PRESSED,
        CMD_BTN_START_LONG_PRESSED,
        CMD_BTN_UP_PRESSED,
        CMD_BTN_DOWN_PRESSED,
        CMD_BTN_NONE
    };

    esp_err_t init() { return m_conn.init(); }

    esp_err_t send(Command_t cmd);

   private:
    McuComm() : m_conn(I2CConnection::getInstance()) { }
    ~McuComm()                         = default;
    McuComm(const McuComm&)            = delete;
    McuComm& operator=(const McuComm&) = delete;

    I2CConnection& m_conn;
};

}  // namespace comm

}  // namespace app
