/**
 * @file mcu_comm.cpp
 * @brief MCU communication handler for I2C commands.
 * @version 0.1
 * @date 2025-08-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "mcu_comm.hpp"

#include <cinttypes>

#include "esp_check.h"

namespace app
{
namespace comm
{
esp_err_t McuComm::send(Command_t cmd)
{
    uint8_t data[] = {static_cast<uint8_t>(cmd)};
    return m_conn.send(data, sizeof(data));
}

}  // namespace comm
}  // namespace app