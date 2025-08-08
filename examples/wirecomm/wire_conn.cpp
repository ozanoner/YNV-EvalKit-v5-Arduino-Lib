/**
 * @file wire_conn.cpp
 * @brief Wire connection handler for I2C communication
 * @version 0.1
 * @date 2025-08-08
 * @copyright Copyright (c) 2025
 */

#include "wire_conn.h"

#include <cassert>

namespace ynv
{
namespace driverv5
{
void WireConnection::init(const ynv::app::AppConfig_t* appConfig, WireDataHandler_t cb)
{
    assert(appConfig != nullptr);
    assert(appConfig->wireAddress >= 0 && appConfig->wireAddress < 0x7F);  // Valid I2C address range

    assert(cb != nullptr);  // Callback function must not be null
    m_callback = cb;

    Wire.begin(appConfig->wireAddress);
    Wire.onReceive(onWireEvent);  // Register the receive event handler
}

void WireConnection::onWireEvent(int howMany)
{
    while (Wire.available() > 1)
    {
        // ignore all but the last byte
        (void)Wire.read();
    }
    WireConnection::getInstance().m_callback(Wire.read());
}

}  // namespace driverv5
}  // namespace ynv