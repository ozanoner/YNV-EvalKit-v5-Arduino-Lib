/**
 * @file mcu_comm.h
 * @brief MCU communication handler for I2C commands
 * This class handles communication with the MCU over I2C, allowing for command processing.
 * Implements the button press events as commands.
 * @version 0.1
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "wire_conn.h"

namespace ynv
{
namespace app
{

/**
 * @brief MCU communication handler for I2C commands
 * This class handles communication with the MCU over I2C, allowing for command processing.
 * It is designed to be used as a singleton.
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

    using CmdCb_f = void (*)(Command_t);

    void init(const ynv::app::AppConfig_t* appConfig);
    void registerCallback(CmdCb_f callback);

   private:
    McuComm() : m_commandCallback(nullptr) { }
    ~McuComm()                         = default;
    McuComm(const McuComm&)            = delete;
    McuComm& operator=(const McuComm&) = delete;

    CmdCb_f m_commandCallback;  // Callback function for command events

    void wireDataHandler(uint8_t data);
};

}  // namespace app
}  // namespace ynv