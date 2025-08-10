# Ynvisible Driver V5 Arduino Library

A modern C++ library for driving Ynvisible electrochromic displays with the Driver v5 board.  
Supports multiple display types, flexible configuration, and built-in animation and communication examples.

You can find the original example here: https://github.com/Ynvisible-Electronics   
More information: https://www.ynvisible.com/   

---

## Features

- Easy-to-use API for controlling Ynvisible displays
- Support for multiple display types (single segment, bar, number, etc.)
- Built-in animation framework for display demos
- Modular, extensible, and uses modern C++ (C++14)

---

## Getting Started

### 1. **Set Compiler Flags**

To enable C++14 features, add the following to your Arduino platform configuration:

Edit  
`~/.arduino15/packages/driver_v5/hardware/samd/1.0.1/platform.txt`  
and append:

```
# Compiler flags
compiler.cpp.extra_flags=-std=gnu++14
```

---

### 2. **Configure Your Application**

Edit `app_config_defs.h` to specify your hardware and application settings. Example:

```cpp
// Specify the display type attached to the EvalKit v5
#define DISPLAY_ATTACHED ynv::ecd::EvalkitDisplays::ECDEvalkitDisplay_t::EVALKIT_DISP_DECIMAL_NUMBER_DISPLAY
// Supply Voltage to the attached ECD
#define SUPPLY_VOLTAGE 3.0f
// Define the ECD driving algorithm (1 for active driving, 0 for passive driving)
#define ACTIVE_DRIVING 1
```

---

### 3. **Example Applications**

- **`examples/evalkit/evalkit.ino`**  
  Demonstrates display selection, animation, and user input handling.

- **`examples/wirecomm/wirecomm.ino`**  
  Shows I2C communication between the EvalKit and another MCU.

- **`examples/wirecomm-esp32`**
  The ESP32 companion app to test the wirecomm example. 

Each example includes a README with usage instructions.

---

## Library Structure

- `src/` – Core library source files
- `examples/` – Example Arduino sketches and supporting code
- `app_config_defs.h` – Application configuration header in the examples

---

## Extending

- Add new display types by subclassing the display base classes.
- Implement custom animations by extending the animation framework.
- Integrate with other MCUs or sensors using the provided communication classes.

