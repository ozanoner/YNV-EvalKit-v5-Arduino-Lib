/**
 * @file i2c_conn.cpp
 * @brief I2C connection handler implementation.
 * @version 0.1
 * @date 2025-08-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "i2c_conn.hpp"

#include "esp_check.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"

#define TAG "app"

namespace app
{
namespace comm
{
esp_err_t I2CConnection::init()
{
    esp_err_t err = ESP_OK;
    if (m_ready)
    {
        return ESP_OK;  // Already initialized
    }

    i2c_master_bus_config_t busConfig = {
        .i2c_port          = 1,
        .sda_io_num        = static_cast<gpio_num_t>(CONFIG_I2C_MASTER_SDA),
        .scl_io_num        = static_cast<gpio_num_t>(CONFIG_I2C_MASTER_SCL),
        .clk_source        = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
    };
    busConfig.flags.enable_internal_pullup = true;

    err = i2c_new_master_bus(&busConfig, &m_busHandle);
    ESP_RETURN_ON_ERROR(err, TAG, "Failed to create I2C master bus: %s", esp_err_to_name(err));

    i2c_device_config_t devConfig = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = CONFIG_I2C_YNV_EVALKIT_ADDRESS,
        .scl_speed_hz    = 100000,  // 100kHz
    };
    err = i2c_master_bus_add_device(m_busHandle, &devConfig, &m_deviceHandle);
    ESP_RETURN_ON_ERROR(err, TAG, "Failed to add I2C device: %s", esp_err_to_name(err));

    m_ready = true;
    return ESP_OK;
}

esp_err_t I2CConnection::send(const uint8_t* const data, size_t len)
{
    esp_err_t err = ESP_OK;
    if (!m_ready)
    {
        return ESP_ERR_INVALID_STATE;
    }

    // 100ms timeout
    err = i2c_master_transmit(m_deviceHandle, data, len, pdTICKS_TO_MS(100));
    ESP_RETURN_ON_ERROR(err, TAG, "Failed to send command: %s", esp_err_to_name(err));

    return ESP_OK;
}

}  // namespace comm
}  // namespace app