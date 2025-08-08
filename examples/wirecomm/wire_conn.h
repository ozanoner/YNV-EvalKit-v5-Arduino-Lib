/**
 * @file wire_conn.h
 * @brief Wire connection handler for I2C communication
 * @version 0.1
 * @date 2025-08-08
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <Arduino.h>
#include <Wire.h>

#include <cstdint>

#include "app_config.h"

namespace ynv
{
namespace driverv5
{
/** @class WireConnection
 * @brief Handles I2C communication using the Wire library
 * This class initializes the Wire connection and provides a callback mechanism for handling incoming data.
 * It is designed to be used as a singleton.
 */
class WireConnection
{
   public:
    using WireDataHandler_t = void (*)(uint8_t);

    static WireConnection& getInstance()
    {
        static WireConnection instance;
        return instance;
    }

    void init(const ynv::app::AppConfig_t* appConfig, WireDataHandler_t cb);

   private:
    WireConnection() : m_wireReady(false), m_callback(nullptr) { }
    ~WireConnection()
    {
        if (m_wireReady)
        {
            Wire.end();  // Clean up Wire connection
        }
    }
    WireConnection(const WireConnection&)            = delete;
    WireConnection& operator=(const WireConnection&) = delete;

    bool              m_wireReady;  // Flag to indicate if Wire is initialized
    WireDataHandler_t m_callback;   // Callback function for wire events

    static void onWireEvent(int howMany);
};
}  // namespace driverv5
}  // namespace ynv