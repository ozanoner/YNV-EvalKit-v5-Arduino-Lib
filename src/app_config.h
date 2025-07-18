
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
    // I2C address of the Driver V5 board
    int wireAddress;
};
}  // namespace app
}  // namespace ynv
