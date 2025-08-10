#pragma once

#include <cinttypes>
#include <cstddef>

#include "driver/i2c_master.h"
#include "esp_err.h"

namespace app
{
namespace comm
{

class I2CConnection
{
   public:
    static I2CConnection& getInstance()
    {
        static I2CConnection instance;
        return instance;
    }

    esp_err_t init();

    esp_err_t send(const uint8_t* const data, size_t len);

   private:
    I2CConnection() : m_busHandle(nullptr), m_deviceHandle(nullptr), m_ready(false) { }
    ~I2CConnection()
    {
        if (m_ready)
        {
            (void)i2c_master_bus_rm_device(m_deviceHandle);
            (void)i2c_del_master_bus(m_busHandle);
        }
    }
    I2CConnection(const I2CConnection&)            = delete;
    I2CConnection& operator=(const I2CConnection&) = delete;

    i2c_master_bus_handle_t m_busHandle;
    i2c_master_dev_handle_t m_deviceHandle;
    bool                    m_ready;
};

}  // namespace comm
}  // namespace app