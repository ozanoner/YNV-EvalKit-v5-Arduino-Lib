/**
 * @file mcu_comm.cpp
 * @brief MCU communication handler for I2C commands
 * @version 0.1
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "mcu_comm.h"

namespace ynv
{
namespace app
{
void McuComm::init(const ynv::app::AppConfig_t* appConfig)
{
    // Initialize Wire
    ynv::driverv5::WireConnection::getInstance().init(
        appConfig, [](uint8_t data) { McuComm::getInstance().wireDataHandler(data); });
}

void McuComm::registerCallback(CmdCb_f callback)
{
    m_commandCallback = callback;
}

void McuComm::wireDataHandler(uint8_t data)
{
    // Handle incoming wire data and trigger the appropriate command callback
    if (m_commandCallback && data < CMD_BTN_NONE)
    {
        m_commandCallback(static_cast<Command_t>(data));
    }
}

}  // namespace app
}  // namespace ynv