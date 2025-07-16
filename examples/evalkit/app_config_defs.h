
#pragma once

// Specify the display type attached to the EvalKit v5
#define DISPLAY_ATTACHED ynv::ecd::EvalkitDisplays::ECDEvalkitDisplay_t::EVALKIT_DISP_DECIMAL_NUMBER_DISPLAY
// Supply Voltage to the attached ECD
#define SUPPLY_VOLTAGE 3.0f
// Define the ECD driving algorithm (1 for active driving, 0 for passive driving)
#define ACTIVE_DRIVING 0
// ADC/DAC resolution, default is 10-bit
#define ANALOG_RESOLUTION 10
// I2C address of the Driver V5 board
#define WIRE_ADDRESS 0x2B