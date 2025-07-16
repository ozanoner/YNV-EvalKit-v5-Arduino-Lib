# Ynvisible Driver V5 Arduino Library

Library for driving the Ynvisible displays with the Driver v5 board.


## Add compiler flag
In the file *~/.arduino15/packages/driver_v5/hardware/samd/1.0.1/platform.txt*, append the following:
```
# Compiler flags
compiler.cpp.extra_flags=-std=gnu++14
```

## Application configuration
Edit the *app_config_def.h* to specify the app-level configuration. Example:
```
// Specify the display type attached to the EvalKit v5
#define DISPLAY_ATTACHED ynv::ecd::EvalkitDisplays::ECDEvalkitDisplay_t::EVALKIT_DISP_DECIMAL_NUMBER_DISPLAY
// Supply Voltage to the attached ECD
#define SUPPLY_VOLTAGE 3.0f
// Define the ECD driving algorithm (1 for active driving, 0 for passive driving)
#define ACTIVE_DRIVING 1
```