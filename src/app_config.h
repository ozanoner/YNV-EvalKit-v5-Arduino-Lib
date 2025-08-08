/**
 * @file app_config.h
 * @brief  Application configuration header
 * This header defines the application configuration structure used throughout the library.
 * @version 0.1
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

namespace ynv
{
namespace app
{
struct AppConfig_t
{
    // Specify the display type attached to the EvalKit v5
    int displayIndex;  // Use ynv::ecd::EvalkitDisplays::ECDEvalkitDisplay_t enum for this
    // Supply Voltage to the attached ECD
    float supplyVoltage;
    // Define the ECD driving algorithm (1 for active driving, 0 for passive driving)
    int activeDriving;
    // ADC/DAC resolution
    int analogResolution;
    // I2C address of the Driver V5 board to use with other MCUs
    int wireAddress;
};
}  // namespace app
}  // namespace ynv
