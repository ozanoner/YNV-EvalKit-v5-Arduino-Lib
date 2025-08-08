# YNV-EvalKit-v5-Arduino-Lib: `wirecomm` Example

This example demonstrates how to use the YNV-EvalKit-v5-Arduino-Lib to communicate with the evaluation kit over I2C using the Arduino Wire library. It shows how to set up the I2C connection, handle incoming commands, and interact with the display and button events.

## Features

- Initializes I2C communication as a slave device.
- Handles commands from a master MCU (such as ESP32).
- Provides a template for integrating I2C-based control into your own projects.

## File Structure

- `wirecomm.ino` – Main Arduino sketch for the example.
- `wire_conn.h/cpp` – Singleton class for managing the I2C (Wire) connection.
- `mcu_comm.h/cpp` – Singleton class for handling MCU commands over I2C.
- `app_config_defs.h` – Application configuration definitions.

## Usage

1. **Connect the EvalKit to your device via I2C.**
   - Make sure the correct I2C address is set in your configuration.

2. **Open `wirecomm.ino` in the Arduino IDE.**

3. **Upload the sketch to your EvalKit-v5 board.**

4. **Interact with the EvalKit using I2C commands from a master device.**
   - The example handles button press events and can be extended to support more commands.

## Key Classes

- **`ynv::driverv5::WireConnection`**
  - Handles low-level I2C communication.
  - Singleton pattern: use `WireConnection::getInstance()`.

- **`ynv::app::McuComm`**
  - Handles higher-level command processing.
  - Singleton pattern: use `McuComm::getInstance()`.

## Extending

- Add new commands in `McuComm::Command_t` enum.
- Implement additional command handling logic in `McuComm`.
- Customize I2C address and configuration in `app_config_def.h`.

## License

See the root project for the licence.